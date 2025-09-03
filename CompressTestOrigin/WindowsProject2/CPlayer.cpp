#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CSceneManager.h"

#include "CTimeMgr.h"

#include "CMissile.h"
#include "CTile.h"
#include "CWhip.h"
#include "CThron.h"
#include "CDoor.h"
#include "CFire.h"

#include "CPathManager.h"
#include "Texture.h"
//#include "CResMgr.h"
#include "TextureManager.h"

#include "CCollider.h"
#include "Animator.h"
#include "CEventMgr.h"
#include "Animation.h"

class Animation;

// 기본 생성자
// 컴포넌트 추가할 곳
CPlayer::CPlayer()
	:m_fMoveDelay(m_fMoveDelayRate),
	m_fAttackDelay(0.0f),
	m_fMoveMent((float)BOARD_TILE),
	m_eCurrDir(OBJECT_DIR::RIGHT),
	m_eprevDir(OBJECT_DIR::RIGHT),
	m_bCanMove(true),
	m_ptBoardPos{},
	m_eCurState(PLAYER_STATE::IDLE),
	m_ePastState(PLAYER_STATE::IDLE),
	m_fTimeLag(m_fMoveDelayRate),
	m_iPoision(0),
	m_bIsLeft(false),
	m_fDieDelay(m_fDieDelayRate),
	m_bIsSlow(-1.0f),
	m_IsOverlap(false)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// Collider 세팅하기
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2(0.f, 5.f));
	GetCollider()->SetScale(Vector2(30.f, 50.f));

	// Texture 로딩하기
	// IDLE texture
	Texture* pTexIdleRight = TextureManager::GetInstance()->LoadTexture(L"Player_IDLE_Right", L"texture\\player_IDLE_Right.bmp");
	Texture* pTexIdleLeft = TextureManager::GetInstance()->LoadTexture(L"Player_IDLE_Left", L"texture\\player_IDLE_Left.bmp");

	// Attack texture
	Texture* pTexAttackLeft = TextureManager::GetInstance()->LoadTexture(L"Player_Attack_Left", L"texture\\Attack_Left.bmp");
	Texture* pTexAttackLRight = TextureManager::GetInstance()->LoadTexture(L"Player_Attack_Right", L"texture\\Attack_Right.bmp");

	// Move texture
	Texture* pTexMoveLeft = TextureManager::GetInstance()->LoadTexture(L"Player_Move_Left", L"texture\\run_left1.bmp");
	Texture* pTexMoveRight = TextureManager::GetInstance()->LoadTexture(L"Player_Move_Right", L"texture\\run_right1.bmp");

	// Dead texture
	Texture* pTexDeadLeft = TextureManager::GetInstance()->LoadTexture(L"Player_Dead_Left", L"texture\\player_die_left.bmp");
	Texture* pTexDeadRight = TextureManager::GetInstance()->LoadTexture(L"Player_Dead_Right", L"texture\\player_die_right.bmp");


	// Animation 세팅하기
	CreateAnimator();
	// IDLE Anmation
	// 전체 68x142 / 가장공간차지하는 캐릭터 60x136
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTexIdleLeft, Vector2(0.f, 0.f), Vector2(68.0f, 142.f), Vector2(68.f, 0.f), 0.3f, 2);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTexIdleRight, Vector2(68.f, 0.f), Vector2(68.0f, 142.f), Vector2(-68.f, 0.f), 0.3f, 2);
	Animation* pAnim = GetAnimator()->FindAnimation(L"IDLE_RIGHT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);

	pAnim = GetAnimator()->FindAnimation(L"IDLE_LEFT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);
	// AttackAnimation
	// 전체 154 x 143 / " 146 x 137
	GetAnimator()->CreateAnimation(L"ATTACK_RIGHT", pTexAttackLRight, Vector2(0.f, 0.f), Vector2(156.0f, 142.f), Vector2(156.0f, 0.f), m_fAttackDelayRate / 8, 8);
	GetAnimator()->CreateAnimation(L"ATTACK_LEFT", pTexAttackLeft, Vector2(156.0f * 7, 0.f), Vector2(156.0f, 142.f), Vector2(-156.0f, 0.f), m_fAttackDelayRate / 8, 8);
	pAnim = GetAnimator()->FindAnimation(L"ATTACK_RIGHT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);
	pAnim = GetAnimator()->FindAnimation(L"ATTACK_LEFT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);


	// MoveAnimation
	// 전체 120 x 142 / " 112 x 136
	GetAnimator()->CreateAnimation(L"MOVE_LEFT", pTexMoveLeft, Vector2(132.0f * 2, 0.0f), Vector2(132.0f, 142.f), Vector2(-132.0f, 0.f), m_fMoveDelayRate / 3, 3);
	
	pAnim = GetAnimator()->FindAnimation(L"MOVE_LEFT");
	pAnim->GetFrame(1).fDuration = 0.0f;
	pAnim->GetFrame(2).fDuration = 0.1f;
	pAnim->GetFrame(3).fDuration = 100.0f;
	pAnim = GetAnimator()->FindAnimation(L"MOVE_LEFT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);
	GetAnimator()->CreateAnimation(L"MOVE_RIGHT", pTexMoveRight, Vector2(0.0f, 0.f), Vector2(132.0f, 142.f), Vector2(132.0f, 0.f), m_fMoveDelayRate / 3, 3);
	
	pAnim = GetAnimator()->FindAnimation(L"MOVE_RIGHT");
	pAnim->GetFrame(1).fDuration = 0.0f;
	pAnim->GetFrame(2).fDuration = 0.1f;
	pAnim->GetFrame(3).fDuration = 100.0f;
	pAnim = GetAnimator()->FindAnimation(L"MOVE_RIGHT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);
	// DeadAnimation
	//전체 128 x 142 / " 120 x 136
	GetAnimator()->CreateAnimation(L"DEAD_LEFT", pTexDeadLeft, Vector2(128.0f * 6, 0.f), Vector2(128.0f, 142.f), Vector2(-128.0f, 0.f), m_fDieDelayRate / 7, 7);
	GetAnimator()->CreateAnimation(L"DEAD_RIGHT", pTexDeadRight, Vector2(0.0f, 0.f), Vector2(128.0f, 142.f), Vector2(128.0f, 0.f), m_fDieDelayRate / 7, 7);
	pAnim = GetAnimator()->FindAnimation(L"DEAD_LEFT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);
	pAnim = GetAnimator()->FindAnimation(L"DEAD_RIGHT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(0.f, -50.f);
	GetAnimator()->Play(L"IDLE_RIGHT", true);

	// Animation Offset 위치 세팅하기 예제
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE");
	//for (int i = 0; i < pAnim->GetMaxFrame(); i++)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -0.f); 
}

CPlayer::~CPlayer()
{
	//delete m_pState;
}

void CPlayer::Update()
{
	if (m_bIsSlow > 0.0f)
	{
		m_bIsSlow -= CTimeManager::GetInstance()->GetfDT();
	}
	else
	{
// 		Animation* pAnim = GetAnimator()->FindAnimation(L"MOVE_LEFT");
// 		pAnim->GetFrame(1).fDuration = 0.0f;
// 		pAnim->GetFrame(2).fDuration = 0.05f;
// 		pAnim->GetFrame(3).fDuration = 0.45f;
// 		pAnim = GetAnimator()->FindAnimation(L"MOVE_RIGHT");
// 		pAnim->GetFrame(1).fDuration = 0.0f;
// 		pAnim->GetFrame(2).fDuration = 0.05f;
// 		pAnim->GetFrame(3).fDuration = 0.45f;
	}
	UpateState();
	UpdateMove();
	UpdateAnimation();
	m_ePastState = m_eCurState;
	m_eprevDir = m_eCurrDir;

	if (m_CollisionOn)
		GetCollider()->SetScale(Vector2(30.f, 50.f));
	else
		GetCollider()->SetScale(Vector2(0.f, 0.f));
}

void CPlayer::Render(HDC _dc)
{
	// 컴포넌트 (충돌체, etc...) 가 있는 경우 렌더
	// 컴포넌트 (Collider, Animator)
	//ComponentRender(_dc);
}

void CPlayer::CreateMissile()
{
	Vector2 vWhipPos = GetPos();
	CWhip* pWhip = new CWhip(m_bIsLeft);
	pWhip->SetName(L"Whip_Player");
	pWhip->SetScale(Vector2(25.f, 25.f));
	pWhip->SetDir(GetDir());

	switch (m_eCurrDir)
	{
		case OBJECT_DIR::UP:
			pWhip->SetPos(vWhipPos + Vector2(0.f, -180.f));
			break;
		case OBJECT_DIR::LEFT:
			pWhip->SetPos(vWhipPos + Vector2(-180.f, 0.f));
			break;
		case OBJECT_DIR::RIGHT:
			pWhip->SetPos(vWhipPos + Vector2(180.f, 0.f));
			break;
		case OBJECT_DIR::DOWN:
			pWhip->SetPos(vWhipPos + Vector2(0.f, 180.f));
			break;
	}

	CreateObject(pWhip, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::UpateState()
{
	if (m_iPoision >= 3)
	{
		m_eCurState = PLAYER_STATE::DEAD;
	}
	if (CheckArrowKey())
	{
		m_fTimeLag -= CTimeManager::GetInstance()->GetfDT();
	}
	else
	{
		m_fTimeLag = m_fTimeLagDelayRate;
	}

	// 현재 상태와 키입력에 따른 상태 변화
	switch (m_eCurState)
	{
		// IDLE 상태의 경우
		case PLAYER_STATE::IDLE:
		{
			Animation* pAnim = GetAnimator()->FindAnimation(L"MOVE_LEFT");
			pAnim->SetFrame(0);
			pAnim = GetAnimator()->FindAnimation(L"MOVE_RIGHT");
			pAnim->SetFrame(0);
			if (CKeyManager::GetInstance()->GetKeyState(KEY::X) != KEY_STATE::HOLD)
			{
				if (!m_IsOverlap)
					m_iPoision = 0;
				// 상하좌우 이동
				if (CKeyManager::GetInstance()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
				{
					SetDir(OBJECT_DIR::UP);
					if (m_fTimeLag <= 0.0f && m_ptBoardPos.y > 0)
					{
						m_ptBoardPos.y--;
						SoundManager::GetInstance()->Play(SOUND::PLAYER_MOVE, SOUND_CHANNAL::EFFECT);
						m_eCurState = PLAYER_STATE::MOVE;
					}
				}
				else if (CKeyManager::GetInstance()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
				{
					SetDir(OBJECT_DIR::DOWN);
					if (m_fTimeLag <= 0.0f && m_ptBoardPos.y < 10)
					{
						SoundManager::GetInstance()->Play(SOUND::PLAYER_MOVE, SOUND_CHANNAL::EFFECT);

						m_ptBoardPos.y++;
						m_eCurState = PLAYER_STATE::MOVE;
					}
				}
				else if (CKeyManager::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
				{
					SetDir(OBJECT_DIR::LEFT);
					m_bIsLeft = true;
					if (m_fTimeLag <= 0.0f && m_ptBoardPos.x > 0)
					{
						SoundManager::GetInstance()->Play(SOUND::PLAYER_MOVE, SOUND_CHANNAL::EFFECT);

						m_ptBoardPos.x--;
						m_eCurState = PLAYER_STATE::MOVE;
					}
				}
				else if (CKeyManager::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
				{
					SetDir(OBJECT_DIR::RIGHT);
					m_bIsLeft = false;
					if (m_fTimeLag <= 0.0f && m_ptBoardPos.x < 17)
					{
						SoundManager::GetInstance()->Play(SOUND::PLAYER_MOVE, SOUND_CHANNAL::EFFECT);

						m_ptBoardPos.x++;
						m_eCurState = PLAYER_STATE::MOVE;
					}
				}
			}


			if (CKeyManager::GetInstance()->GetKeyState(KEY::X) == KEY_STATE::HOLD)
			{
				if (GetDir() == OBJECT_DIR::RIGHT || GetDir() == OBJECT_DIR::LEFT)
					m_eCurState = PLAYER_STATE::ATTACK;
			}

			break;
		}
		// 움직임 딜레이인 경우
		case PLAYER_STATE::MOVE_DELAY:
		{
			m_fMoveDelay += CTimeManager::GetInstance()->GetfDT();
			if (m_fMoveDelay >= m_fMoveDelayRate)
			{
				m_eCurState = PLAYER_STATE::IDLE;
				m_fMoveDelay = 0.0f;
			}
			break;
		}


		// 공격 딜레이인 경우
		case PLAYER_STATE::ATTACK_DELAY:
		{
			m_fAttackDelay += CTimeManager::GetInstance()->GetfDT();
			if (m_fAttackDelay >= m_fAttackDelayRate)
			{
				m_eCurState = PLAYER_STATE::IDLE;
				m_fAttackDelay = 0.0f;
			}
			break;
		}

		// 죽은 경우
		case PLAYER_STATE::DEAD:
		{
			m_fDieDelay -= CTimeManager::GetInstance()->GetfDT();
			if (m_fDieDelay <= 0)
			{
				m_fDieDelay = m_fDieDelayRate;
				ChangeScene(CSceneManager::GetInstance()->GetCurScene()->m_eNowScene);
				CPlayer::m_siDeathCount++;
			}
			break;
		}
		case PLAYER_STATE::ATTACK:
			m_eCurState = PLAYER_STATE::ATTACK_DELAY;
			break;
		default:
			break;
	}
}

void CPlayer::UpdateMove()
{
	switch (m_eCurState)
	{
		case PLAYER_STATE::MOVE:
		{
			Vector2 curPos = GetPos();
			m_fMoveDelay += CTimeManager::GetInstance()->GetfDT();
			float movingTime = m_bIsSlow <= 0.0f ? 0.2f : 0.2f + m_fSlowRate;
			// 0.2초 안에 움직이기
			if (m_fMoveDelay <= movingTime)
			{
				switch (m_eCurrDir)
				{
					case OBJECT_DIR::UP:
						curPos.y -= m_fMoveMent * CTimeManager::GetInstance()->GetfDT() / movingTime;
						break;
					case OBJECT_DIR::LEFT:

						curPos.x -= m_fMoveMent * CTimeManager::GetInstance()->GetfDT() / movingTime;
						break;
					case OBJECT_DIR::RIGHT:
						curPos.x += m_fMoveMent * CTimeManager::GetInstance()->GetfDT() / movingTime;
						break;
					case OBJECT_DIR::DOWN:

						curPos.y += m_fMoveMent * CTimeManager::GetInstance()->GetfDT() / movingTime;
						break;
					default:
						break;
				}
				SetPos(curPos);
			}
			else
			{
				m_fMoveDelay = 0.2f;
				curPos = Vector2{ (int)(m_ptBoardPos.x) * BOARD_TILE + BOARD_TILE / 2, (int)m_ptBoardPos.y * BOARD_TILE + BOARD_TILE / 2 };
				SetPos(curPos);
				m_eCurState = PLAYER_STATE::MOVE_DELAY;
			}
		}
		break;

		case PLAYER_STATE::ATTACK:
		{
			CreateMissile();
		}

		case PLAYER_STATE::DEAD:
			break;
		default:
			break;
	}
}

void CPlayer::UpdateAnimation()
{
	switch (m_eCurState)
	{
		case PLAYER_STATE::IDLE:
			switch (m_eCurrDir)
			{
				case OBJECT_DIR::LEFT:
					GetAnimator()->Play(L"IDLE_LEFT", true);
					break;
				case OBJECT_DIR::RIGHT:
					GetAnimator()->Play(L"IDLE_RIGHT", true);
					break;
				case OBJECT_DIR::UP:
				case OBJECT_DIR::DOWN:
				{
					if (m_bIsLeft)
					{
						GetAnimator()->Play(L"IDLE_LEFT", true);
					}
					else
					{
						GetAnimator()->Play(L"IDLE_RIGHT", true);
					}
					break;
				}
				default:
					break;
			}
			break;
		case PLAYER_STATE::MOVE_DELAY:
		case PLAYER_STATE::MOVE:
			switch (m_eCurrDir)
			{
				case OBJECT_DIR::LEFT:
					GetAnimator()->Play(L"MOVE_LEFT", false);
					break;
				case OBJECT_DIR::RIGHT:
					GetAnimator()->Play(L"MOVE_RIGHT", false);
					break;
				case OBJECT_DIR::UP:
				case OBJECT_DIR::DOWN:
				{
					if (m_bIsLeft)
					{
						GetAnimator()->Play(L"MOVE_LEFT", false);
					}
					else
					{
						GetAnimator()->Play(L"MOVE_RIGHT", false);
					}
					break;
				}

				default:
					break;
			}
			break;
		case PLAYER_STATE::ATTACK:
			break;
		case PLAYER_STATE::ATTACK_DELAY:
		{
			switch (m_eCurrDir)
			{
				case OBJECT_DIR::UP:
				case OBJECT_DIR::DOWN:
				{
					if (m_bIsLeft)
					{
						GetAnimator()->Play(L"ATTACK_LEFT", false);
					}
					else
					{
						GetAnimator()->Play(L"ATTACK_RIGHT", false);
					}
					break;
				}
				case OBJECT_DIR::LEFT:
					GetAnimator()->Play(L"ATTACK_LEFT", false);
					break;
				case OBJECT_DIR::RIGHT:
					GetAnimator()->Play(L"ATTACK_RIGHT", false);

					break;
				default:
					break;
			}
			break;
		}
		case PLAYER_STATE::DEAD:
		{
			if (m_bIsLeft)
			{
				GetAnimator()->Play(L"DEAD_LEFT", false);
			}
			else
			{
				GetAnimator()->Play(L"DEAD_RIGHT", false);
			}
			break;
		}
		default:
			break;
	}


}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	// 현재 콜리전 충돌
	m_IsOverlap = true;

	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Tile")
	{
		CTile* pTile;
		pTile = dynamic_cast<CTile*>(pOtherObj);

		switch ((TILE_TYPE)pTile->GetTileType())
		{
			case TILE_TYPE::MOVABLE:
				break;
			case TILE_TYPE::WALL:
			{
				Vector2 curPos = GetPos();
				// 벽 타일 충돌 처리
				switch (m_eCurrDir)
				{
					case OBJECT_DIR::UP:
						m_ptBoardPos.y++;
						break;
					case OBJECT_DIR::LEFT:
						m_ptBoardPos.x++;
						break;
					case OBJECT_DIR::RIGHT:
						m_ptBoardPos.x--;
						break;
					case OBJECT_DIR::DOWN:
						m_ptBoardPos.y--;
						break;
					default:
						break;
				}
				m_fMoveDelay = 0.2f;
				curPos = Vector2{ (int)(m_ptBoardPos.x) * BOARD_TILE + BOARD_TILE / 2, (int)m_ptBoardPos.y * BOARD_TILE + BOARD_TILE / 2 };
				SetPos(curPos);
				m_eCurState = PLAYER_STATE::MOVE_DELAY;
				break;
			}


			case TILE_TYPE::TRAP:
				break;
			case TILE_TYPE::POSION:
				break;
			case TILE_TYPE::FIRE:						// 가시 타일, 가시가 올라온 상태라면 플레이어가 죽도록 처리 ( 추가 : 이건재 )
			{
				if (pTile->GetThron()->GetIsOn())
				{
					SoundManager::GetInstance()->Play(PLAYER_DEAD, EFFECT);
					m_eCurState = PLAYER_STATE::DEAD;
				}
				break;
			}
			case TILE_TYPE::SCENE_CHANGE:
			{
				// 씬 교체 타일 충돌 처리
				ChangeScene(CSceneManager::GetInstance()->GetCurScene()->m_eNextScene);
				break;
			}
			case TILE_TYPE::TRIGGER:
				break;

			case TILE_TYPE::TRIGGER_MOVABLE:
				break;
			case TILE_TYPE::END:
				break;
			default:
				break;
		}

		if (pTile->GetTileType() == (int)TILE_TYPE::POSION)
		{
		
			m_iPoision++;
			// 독 타일 충돌 처리
			SoundManager::GetInstance()->Play(EFFECT_POISON, EFFECT);
			
		}
		else
		{
			m_iPoision = 0;
		}
	}

	if (pOtherObj->GetName() == L"Guardian")
	{
		SoundManager::GetInstance()->Play(PLAYER_DEAD, EFFECT);
		m_eCurState = PLAYER_STATE::DEAD;
	}

	if (pOtherObj->GetName() == L"Fire_Trap")
	{
		SoundManager::GetInstance()->Play(PLAYER_DEAD, EFFECT);
		CFire* pFire = (CFire*)pOtherObj;
		if (pFire->TriggerOn)
			m_eCurState = PLAYER_STATE::DEAD;
	}
	if (pOtherObj->GetName() == L"Missile_Trap")
	{
		SoundManager::GetInstance()->Play(PLAYER_DEAD, EFFECT);
		m_eCurState = PLAYER_STATE::DEAD;
	}
	if (pOtherObj->GetName() == L"Spider")
	{
// 		Animation* pAnim = GetAnimator()->FindAnimation(L"MOVE_LEFT");
// 		pAnim->GetFrame(1).fDuration = 0.0f;
// 		pAnim->GetFrame(2).fDuration = 0.4f;
// 		pAnim->GetFrame(3).fDuration = 0.6f;
// 		pAnim = GetAnimator()->FindAnimation(L"MOVE_RIGHT");
// 		pAnim->GetFrame(1).fDuration = 0.0f;
// 		pAnim->GetFrame(2).fDuration = 0.4f;
// 		pAnim->GetFrame(3).fDuration = 0.6f;
		m_bIsSlow = m_fSlowTime;
	}

	if (pOtherObj->GetName() == L"Door")
	{
		CDoor* pDoor = dynamic_cast<CDoor*>(pOtherObj);

		if (pDoor->GetDoorState() == false)
		{
			Vector2 curPos = GetPos();
			// 벽 타일 충돌 처리
			switch (m_eCurrDir)
			{
				case OBJECT_DIR::UP:
					m_ptBoardPos.y++;
					break;
				case OBJECT_DIR::LEFT:
					m_ptBoardPos.x++;
					break;
				case OBJECT_DIR::RIGHT:
					m_ptBoardPos.x--;
					break;
				case OBJECT_DIR::DOWN:
					m_ptBoardPos.y--;
					break;
				default:
					break;
			}
			m_fMoveDelay = 0.2f;
			curPos = Vector2{ (int)(m_ptBoardPos.x + 3) * BOARD_TILE + BOARD_TILE / 2, (int)m_ptBoardPos.y * BOARD_TILE + BOARD_TILE / 2 };
			SetPos(curPos);
			m_eCurState = PLAYER_STATE::MOVE_DELAY;
		}
	}
	if (pOtherObj->GetName() == L"StageRelics")
	{
		ChangeScene(CSceneManager::GetInstance()->GetCurScene()->m_eNextScene);
	}
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Tile")
	{
		CTile* pTile;
		pTile = dynamic_cast<CTile*>(pOtherObj);
		if ((pTile->GetTileType() == (UINT)TILE_TYPE::FATAL))
		{
			if (!(m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::MOVE_DELAY))
			{
				if (m_eCurState != PLAYER_STATE::DEAD)
				{
					SoundManager::GetInstance()->Play(SOUND::PLAYER_DEAD, SOUND_CHANNAL::EFFECT);
				}
				m_eCurState = PLAYER_STATE::DEAD;
				// 낙사 타일 충돌 처리
			}
		}
		if ((pTile->GetTileType() == (UINT)TILE_TYPE::FIRE))
		{
			if (pTile->GetThron()->GetIsOn())
			{
				if (m_eCurState != PLAYER_STATE::DEAD)
				{
					// SoundManager::GetInstance()->Play(SOUND::PLAYER_DEAD, SOUND_CHANNAL::EFFECT);
				}
				m_eCurState = PLAYER_STATE::DEAD;
			}
		}
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	// 현재 콜리전 충돌 해제
	m_IsOverlap = false;
}
