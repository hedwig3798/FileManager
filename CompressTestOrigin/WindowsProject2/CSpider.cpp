#include "pch.h"
#include "CSpider.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "Texture.h"

#include <cmath>

class CCollider;

CSpider::CSpider()
	: m_ePrevState(MONSTER_STATE::IDLE)
	, m_eCurrState(MONSTER_STATE::IDLE)
	, m_ptBoardPos{}
	, m_bCanMove(false)
	, m_ePrevDir(OBJECT_DIR::UP)
	, m_eCurrDir(OBJECT_DIR::UP)
	, m_fMoveMent((float)BOARD_TILE)
	, m_vChasePos{}
{
	//m_mTex = CResMgr::GetInstance()->LoadTexture(L"Spider", L"texture\\spider_01.bmp");
	m_mTex = TextureManager::GetInstance()->LoadTexture(L"Spider", L"texture\\spider_01.bmp");
// 	int iWidth = (int)m_mTex->Width();
// 	int iHeight = (int)m_mTex->Height();
// 	StretchBlt(
// 		m_mTex->GetDC(),
// 		0, 0
// 		, (int)((float)(iWidth / 8)) * 2
// 		, (int)((float)(iHeight / 8)) * 2
// 		, m_mTex->GetDC()
// 		, 0, 0
// 		, (int)((float)(iWidth / 8)) / 2
// 		, (int)((float)(iHeight / 8)) / 2
// 		, SRCCOPY
// 	);
}

CSpider::~CSpider()
{

}

void CSpider::Update()
{
	UpateState();
	UpdateMove();
	UpdateAnimation();
}

void CSpider::Render(HDC _dc)
{
	int iWidth = (int)m_mTex->Width();
	int iHeight = (int)m_mTex->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(
		_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_mTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	//ComponentRender(_dc);
}

void CSpider::UpateState()
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
			float totalDis = sqrt(xDis * xDis + yDis * yDis);
			if (totalDis <= (float)(BOARD_TILE))
			{
				SoundManager::GetInstance()->Play(SOUND::ENEMY_MOVE, SOUND_CHANNAL::EFFECT);

				m_eCurrState = MONSTER_STATE::CHASE;
				m_vChasePos = pPos;
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
	}
	break;
	default:
		break;
	}
}

void CSpider::UpdateMove()
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
		if (m_fMoveDelay <= 0.2f)
		{
			switch (m_eCurrDir)
			{
			case OBJECT_DIR::UP:
				curPos.y -= m_fMoveMent * CTimeManager::GetInstance()->GetfDT() * 5;
				break;
			case OBJECT_DIR::LEFT:
				curPos.x -= m_fMoveMent * CTimeManager::GetInstance()->GetfDT() * 5;
				break;
			case OBJECT_DIR::RIGHT:
				curPos.x += m_fMoveMent * CTimeManager::GetInstance()->GetfDT() * 5;
				break;
			case OBJECT_DIR::DOWN:
				curPos.y += m_fMoveMent * CTimeManager::GetInstance()->GetfDT() * 5;
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

void CSpider::UpdateAnimation()
{

}

void CSpider::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Whip_Player" || _pOther->GetObj()->GetName() == L"Player")
	{
		SoundManager::GetInstance()->Play(SOUND::ENEMY_DEAD, SOUND_CHANNAL::EFFECT);

		DeleteObject(this);
	}
}

