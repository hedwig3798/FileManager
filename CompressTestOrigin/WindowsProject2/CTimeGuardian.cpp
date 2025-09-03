#include "pch.h"
#include "CTimeGuardian.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include <cmath>
#include "CTile.h"

class CColider;

CTimeGuardian::CTimeGuardian()
	: m_ePrevState(MONSTER_STATE::IDLE)
	, m_eCurrState(MONSTER_STATE::IDLE)
	, m_ptBoardPos{}
	, m_bCanMove(false)
	, m_ePrevDir(OBJECT_DIR::UP)
	, m_eCurrDir(OBJECT_DIR::UP)
	, m_fMoveMent((float)BOARD_TILE)
	, m_vChasePos{}
	, m_bIsLeft(true)
	, m_fStunDelay(0)
	, m_bIsTargeting(false)
{
	//m_mTextureLeft = CResMgr::GetInstance()->LoadTexture(L"time_guardian_left", L"texture\\time_guradian_left.bmp");
	m_mTextureLeft = TextureManager::GetInstance()->LoadTexture(L"time_guardian_left", L"texture\\time_guradian_left.bmp");
	//m_mTextureRight = CResMgr::GetInstance()->LoadTexture(L"time_guardian_right", L"texture\\time_guradian_right.bmp");
	m_mTextureRight = TextureManager::GetInstance()->LoadTexture(L"time_guardian_right", L"texture\\time_guradian_right.bmp");
}

CTimeGuardian::~CTimeGuardian()
{

}

void CTimeGuardian::Update()
{
	UpateState();
	UpdateMove();
	UpdateAnimation();
}

void CTimeGuardian::Render(HDC _dc)
{
	Texture* now = nullptr;
	if (m_bIsLeft)
	{
		now = m_mTextureLeft;
	}
	else
	{
		now = m_mTextureRight;
	}
	int iWidth = (int)now->Width();
	int iHeight = (int)now->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(
		_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2)) - 100
		, iWidth, iHeight
		, now->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);
	//ComponentRender(_dc);
}

void CTimeGuardian::UpateState()
{
	switch (m_eCurrState)
	{
		case MONSTER_STATE::IDLE:
		{
			vector<CObject*> player = CSceneManager::GetInstance()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER);
			for (auto p : player)
			{
				Vector2 pPos = p->GetPos();
				Vector2 mPos = GetPos();
				float xDis = pPos.x - mPos.x;
				float yDis = pPos.y - mPos.y;

				if (abs(xDis) <= BOARD_TILE * 2 && abs(yDis) <= BOARD_TILE * 2 || m_bIsTargeting)
				{
					m_bIsTargeting = true;
					m_eCurrState = MONSTER_STATE::CHASE;
					m_vChasePos = pPos;
					SoundManager::GetInstance()->Play(SOUND::ENEMYGUARDIAN_MOVE, SOUND_CHANNAL::EFFECT);
					if (xDis <= -(float)BOARD_TILE && xDis <= 0.0f)
					{
						m_eCurrDir = OBJECT_DIR::LEFT;
						m_ptBoardPos.x--;
					}
					else if (xDis >= (float)BOARD_TILE && xDis >= 0.0f)
					{
						m_eCurrDir = OBJECT_DIR::RIGHT;
						m_ptBoardPos.x++;
					}
					else if (yDis <= -(float)BOARD_TILE && yDis <= 0.0f)
					{
						m_eCurrDir = OBJECT_DIR::UP;
						m_ptBoardPos.y--;
					}
					else if (yDis >= (float)BOARD_TILE && yDis >= 0.0f)
					{
						m_eCurrDir = OBJECT_DIR::DOWN;
						m_ptBoardPos.y++;
					}
				}
			}
		}
		break;
		case MONSTER_STATE::CHASE:
			break;
		case MONSTER_STATE::DELAY:
		{
			m_fMoveDelay += CTimeManager::GetInstance()->GetfDT();
			if (m_fMoveDelay >= m_fMoveDelayRate)
			{
				m_eCurrState = MONSTER_STATE::IDLE;
				m_fMoveDelay = 0.0f;
			}
			break;
		}
		case MONSTER_STATE::STUN:
		{
			m_fStunDelay -= CTimeManager::GetInstance()->GetfDT();
			if (m_fStunDelay <= 0)
			{
				m_eCurrState = MONSTER_STATE::IDLE;
			}
			break;
		}

		default:
			break;
	}
}

void CTimeGuardian::UpdateMove()
{
	switch (m_eCurrState)
	{
		case MONSTER_STATE::IDLE:
			break;
		case MONSTER_STATE::CHASE:
		{
			Vector2 curPos = GetPos();
			m_fMoveDelay += CTimeManager::GetInstance()->GetfDT();
			// 0.2초 안에 움직이기
			float movingTime = 0.5f;
			if (m_fMoveDelay <= 0.5f)
			{
				switch (m_eCurrDir)
				{
					case OBJECT_DIR::UP:
						curPos.y -= m_fMoveMent * CTimeManager::GetInstance()->GetfDT() / movingTime;
						break;
					case OBJECT_DIR::LEFT:
						m_bIsLeft = true;
						curPos.x -= m_fMoveMent * CTimeManager::GetInstance()->GetfDT() / movingTime;
						break;
					case OBJECT_DIR::RIGHT:
						m_bIsLeft = false;
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
				curPos = Vector2{ (int)(m_ptBoardPos.x + 3) * BOARD_TILE + BOARD_TILE / 2, (int)m_ptBoardPos.y * BOARD_TILE + BOARD_TILE / 2 };
				SetPos(curPos);
				m_eCurrState = MONSTER_STATE::DELAY;
			}
		}
		break;
		case MONSTER_STATE::DELAY:
			break;
		default:
			break;
	}
}

void CTimeGuardian::UpdateAnimation()
{

}

void CTimeGuardian::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Whip_Player")
	{
		SoundManager::GetInstance()->Play(SOUND::ENEMYGUARDIAN_HIT, SOUND_CHANNAL::EFFECT);

		m_eCurrState = MONSTER_STATE::STUN;
		m_fStunDelay = m_fStunDelayRate;
	}

	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Tile")
	{
		CTile* pTile;
		pTile = dynamic_cast<CTile*>(pOtherObj);
		if (pTile->GetTileType() == (UINT)TILE_TYPE::FATAL)
		{
			SoundManager::GetInstance()->Play(SOUND::ENEMYGUARDIAN_HIT, SOUND_CHANNAL::EFFECT);

			DeleteObject(this);
			// 낙사 타일 충돌 처리
		}

		if (pTile->GetTileType() == (UINT)TILE_TYPE::WALL)
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
			m_eCurrState = MONSTER_STATE::DELAY;
		}
	}
}
