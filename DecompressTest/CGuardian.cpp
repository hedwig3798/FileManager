#include "pch.h"
#include "CGuardian.h"
//#include "CResMgr.h"
#include "TextureManager.h"
#include "CSceneManager.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "Animator.h"
#include "CCollider.h"
#include <random>
#include "Animation.h"
class CColider;

CGuardian::CGuardian()
	: m_eCurrState(MONSTER_STATE_G::IDLE)
	, m_eAttackDir(OBJECT_DIR::LEFT)
	, m_fMoveDelay(m_fMoveDelayRate)
	, m_fAttackDelay(m_fAttackDelayRate)
	, m_fMoveMent(BOARD_TILE)
	, m_iMoveRange(1)
	, m_iMovePoint(1)
	, m_bIsHorizen(false)
	, m_ptCenter{}
	, m_bIsLeft(false)
	, m_bCanMove(true)
{
	// 가디언 IDLE
	//Texture * pTexIdleRight = CResMgr::GetInstance()->LoadTexture(L"Guardian_IDLE_Right", L"texture\\guardian_right.bmp");
	Texture * pTexIdleRight = TextureManager::GetInstance()->LoadTexture(L"Guardian_IDLE_Right", L"texture\\guardian_right.bmp");
	//Texture * pTexIdleLeft = CResMgr::GetInstance()->LoadTexture(L"Guardian_IDLE_Left", L"texture\\guardian_left.bmp");
	Texture * pTexIdleLeft = TextureManager::GetInstance()->LoadTexture(L"Guardian_IDLE_Left", L"texture\\guardian_left.bmp");

	//Texture* pTexAttackRight = CResMgr::GetInstance()->LoadTexture(L"Guardian_Attack_Right", L"texture\\guardian_attack_right.bmp");
	Texture* pTexAttackRight = TextureManager::GetInstance()->LoadTexture(L"Guardian_Attack_Right", L"texture\\guardian_attack_right.bmp");
	//Texture* pTexAttackLeft = CResMgr::GetInstance()->LoadTexture(L"Guardian_Attack_Left", L"texture\\guardian_attack_left.bmp");
	Texture* pTexAttackLeft = TextureManager::GetInstance()->LoadTexture(L"Guardian_Attack_Left", L"texture\\guardian_attack_left.bmp");

	CreateAnimator();
	//guardian 전체 111 x 238 / " 103 x 232
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTexIdleLeft, Vector2(0.f, 0.f), Vector2(175.0f, 238.f), Vector2(111.0f, 0.f), 0.01f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTexIdleRight, Vector2(0.f, 0.f), Vector2(175.0f, 238.f), Vector2(111.0f, 0.f), 0.01f, 1);
	Animation* pAnim = GetAnimator()->FindAnimation(L"IDLE_LEFT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(-30.f, -90.0f);
	pAnim = GetAnimator()->FindAnimation(L"IDLE_RIGHT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(-30.f, -90.0f);
	// 전체 175 x 256 / " 167x250
	GetAnimator()->CreateAnimation(L"ATTACK_LEFT", pTexAttackLeft, Vector2(175.0f * 2, 0.f), Vector2(175.0f, 256.f), Vector2(-175.0f, 0.f), m_fAttackDelayRate / 3, 3);
	GetAnimator()->CreateAnimation(L"ATTACK_RIGHT", pTexAttackRight, Vector2(0.f, 0.f), Vector2(175.0f, 256.f), Vector2(175.0f, 0.f), m_fAttackDelayRate / 3, 3);
	GetAnimator()->Play(L"IDLE_LEFT", true);
	pAnim = GetAnimator()->FindAnimation(L"ATTACK_LEFT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(-30.f, -90.0f);
	pAnim = GetAnimator()->FindAnimation(L"ATTACK_RIGHT");
	for (int i = 1; i < pAnim->GetMaxFrame() + 1; i++)
		pAnim->GetFrame(i).vOffset = Vector2(-30.f, -90.0f);
}

CGuardian::~CGuardian()
{

}

void CGuardian::Update()
{
	UpateState();
	UpdateMove();
	UpdateAnimation();
}

void CGuardian::Render(HDC _dc)
{
	//ComponentRender(_dc);
}

void CGuardian::UpateState()
{
	switch (m_eCurrState)
	{
	case MONSTER_STATE_G::IDLE:
	{
		vector<CObject*> player = CSceneManager::GetInstance()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER);
		for (auto p : player) {
			
			Vector2 pPos = p->GetPos();
			Vector2 mPos = GetPos();
			int xDis = (int)round((pPos.x - mPos.x) / 120.0f);
			int yDis = (int)round((pPos.y - mPos.y) / 120.0f);

			if (xDis > 0)
			{
				m_bIsLeft = false;
			}
			else
			{
				m_bIsLeft = true;
			}

			if (xDis == 0 && yDis >= 0) 
			{
				m_eAttackDir = OBJECT_DIR::DOWN;
				m_eCurrState = MONSTER_STATE_G::ATTACK;
			}
			else if (xDis == 0 && yDis <= 0)
			{
				m_eAttackDir = OBJECT_DIR::UP;
				m_eCurrState = MONSTER_STATE_G::ATTACK;
			}
			else if (yDis == 0 && xDis >= 0)
			{
				m_eAttackDir = OBJECT_DIR::RIGHT;
				m_eCurrState = MONSTER_STATE_G::ATTACK;
			}
			else if (yDis == 0 && xDis <= 0)
			{
				m_eAttackDir = OBJECT_DIR::LEFT;
				m_eCurrState = MONSTER_STATE_G::ATTACK;
			}
			else 
			{
				if (m_bCanMove) 
				{
					SoundManager::GetInstance()->Play(SOUND::ENEMYGUARDIAN_MOVE, SOUND_CHANNAL::EFFECT);

					m_eCurrState = MONSTER_STATE_G::PATROL;
					if (m_bIsHorizen)
					{
						m_ptBoardPos.x += m_iMovePoint;
					}
					else
					{
						m_ptBoardPos.y += m_iMovePoint;
					}
				}
				
			}
		}
		break;
	}
	case MONSTER_STATE_G::PATROL_DELAY:
	{
		m_fMoveDelay += CTimeManager::GetInstance()->GetfDT();
		if (m_fMoveDelay >= m_fMoveDelayRate)
		{
			m_eCurrState = MONSTER_STATE_G::IDLE;
			m_fMoveDelay = 0.0f;
		}
		break;
	}
	case MONSTER_STATE_G::ATTACK_DELAY:
	{
		m_fAttackDelay += CTimeManager::GetInstance()->GetfDT();
		if (m_fAttackDelay >= m_fAttackDelayRate)
		{
			m_eCurrState = MONSTER_STATE_G::IDLE;
			m_fAttackDelay = 0.0f;
		}
		break;
	}
	case MONSTER_STATE_G::STUN:
	{
		m_fStunDelay -= CTimeManager::GetInstance()->GetfDT();
		if (m_fStunDelay <= 0)
		{
			m_eCurrState = MONSTER_STATE_G::IDLE;
		}
		break;
	}
	default:
		break;
	}
}

void CGuardian::UpdateMove()
{
	switch (m_eCurrState)
	{
	case MONSTER_STATE_G::PATROL:
	{
		Vector2 curPos = GetPos();
		m_fMoveDelay += CTimeManager::GetInstance()->GetfDT();
		// 0.2초 안에 움직이기
		if (m_fMoveDelay <= 0.2f)
		{
			if (m_bIsHorizen) 
			{
				curPos.x += m_fMoveMent * CTimeManager::GetInstance()->GetfDT() * 5 * m_iMovePoint;
			}
			else
			{
				curPos.y += m_fMoveMent * CTimeManager::GetInstance()->GetfDT() * 5 * m_iMovePoint;
			}
			SetPos(curPos);
		}
		else
		{
			m_fMoveDelay = 0.2f;
			curPos = Vector2{ (int)(m_ptBoardPos.x) * BOARD_TILE + BOARD_TILE / 2, (int)m_ptBoardPos.y * BOARD_TILE + BOARD_TILE / 2 };
			SetPos(curPos);
			if (abs(m_ptBoardPos.x - m_ptCenter.x) >= m_iMoveRange || abs(m_ptBoardPos.y - m_ptCenter.y) >= m_iMoveRange)
			{
				m_iMovePoint *= -1;
			}
			m_eCurrState = MONSTER_STATE_G::PATROL_DELAY;
		}
		break;
	}
	case MONSTER_STATE_G::ATTACK:
		CreateMissile();
		m_eCurrState = MONSTER_STATE_G::ATTACK_DELAY;
		break;
	default:
		break;
	}
}

void CGuardian::UpdateAnimation()
{
	switch (m_eCurrState)
	{
		case MONSTER_STATE_G::STUN:
	case MONSTER_STATE_G::IDLE:
		if (m_bIsLeft) 
		{
			GetAnimator()->Play(L"IDLE_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		}
		break;
	case MONSTER_STATE_G::PATROL:
		break;
	case MONSTER_STATE_G::ATTACK:
		break;
	case MONSTER_STATE_G::PATROL_DELAY:
		break;

	case MONSTER_STATE_G::ATTACK_DELAY:
		if (m_bIsLeft) 
		{
			GetAnimator()->Play(L"ATTACK_LEFT", false);
		}
		else
		{
			GetAnimator()->Play(L"ATTACK_RIGHT", false);
		}
		
		break;
	default:
		break;
	}
}

void CGuardian::CreateMissile()
{
	Vector2 vMissilePos = GetPos();
	if (m_bIsLeft) 
	{
		vMissilePos.x -= 20.f;
	}
	else
	{
		vMissilePos.x += 40.f;
	}
	
	vMissilePos.y -= 30.f;
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Trap");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vector2(25.f, 25.f));
	pMissile->SetDir(m_eAttackDir);
	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
	
}

void CGuardian::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Whip_Player")
	{
		m_eCurrState = MONSTER_STATE_G::STUN;
		SoundManager::GetInstance()->Play(SOUND::ENEMYGUARDIAN_HIT, SOUND_CHANNAL::EFFECT);

		m_fStunDelay = m_fStunDelayRate;
	}
}

