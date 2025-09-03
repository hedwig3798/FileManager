///missile이 화살이다 
#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CTile.h"

CMissile::CMissile()
	: m_fTheta((float)PI / 2.f)
	, m_dir{}
	, m_fLifeTiem(100.0f)
	, m_iIndex(0)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(24.f, 24.f));
	m_pMissileTexture[0] = TextureManager::GetInstance()->LoadTexture(L"MissileUP", L"texture\\ArrowToUP.bmp");	//위로발사
	m_pMissileTexture[1] = TextureManager::GetInstance()->LoadTexture(L"MissileDOWN", L"texture\\ArrowToDOWN.bmp");	//아래로발사
	m_pMissileTexture[2] = TextureManager::GetInstance()->LoadTexture(L"MissileLEFT", L"texture\\ArrowToLEFT.bmp");	//왼쪽으로발사
	m_pMissileTexture[3] = TextureManager::GetInstance()->LoadTexture(L"MissileRIGHT", L"texture\\ArrowToRight.bmp");	//오른쪽으로발사
}

CMissile::~CMissile()
{
}

void CMissile::Update()
{
	m_fLifeTiem -= CTimeManager::GetInstance()->GetfDT();
	if (m_fLifeTiem <= 0)
	{
		DeleteObject(this);
	}

	Vector2 vPos = GetPos();

	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y += 600.f * sinf(m_fTheta) * fDT;

	switch (m_dir)
	{
		case OBJECT_DIR::UP:
		{
			m_iIndex = 0;
			vPos.y -= 3.0f * BOARD_TILE * CTimeManager::GetInstance()->GetfDT();
		}
		break;
		case OBJECT_DIR::DOWN:
		{
			m_iIndex = 1;
			vPos.y += 3.0f * BOARD_TILE * CTimeManager::GetInstance()->GetfDT();
		}
		break;
		case OBJECT_DIR::LEFT:
		{
			m_iIndex = 2;
			vPos.x -= 3.0f * BOARD_TILE * CTimeManager::GetInstance()->GetfDT();
		}
		break;
		case OBJECT_DIR::RIGHT:
		{
			m_iIndex = 3;
			vPos.x += 3.0f * BOARD_TILE * CTimeManager::GetInstance()->GetfDT();
		}
		break;
		default:
			break;
	}

	SetPos(vPos);
}


void CMissile::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	int w = m_pMissileTexture[m_iIndex]->Width();
	int h = m_pMissileTexture[m_iIndex]->Height();
	int x = 0;
	int y = 0;
	
	///타원함수로 그려서 원 나오는거였어
// 	Ellipse(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2)
// 		, (int)(vPos.x + vScale.x / 2), (int)(vPos.y + vScale.y / 2));

	//ComponentRender(_dc);
	///화살너무 작게나오니까 크게해야된다. if문 안에서 해결한다
	if ((m_iIndex) == 0 || (m_iIndex) == 1)
	{
		vScale.x = vScale.x * 1.25f;
		vScale.y = vScale.y * 2.5f;
		TransparentBlt(_dc
			, (int)(vPos.x /*+ vScale.x / 4*/)
			, (int)(vPos.y /*+ vScale.y / 4*/)
			, (int)(vScale.x /*/ 2*/)
			, (int)(vScale.y /*/ 2*/)
			, m_pMissileTexture[m_iIndex]->GetDC()		///생성자에 있는 rand함수에 의해 m_iIndex가 0,1,2중 랜덤으로 정해진다
			, x
			, y
			, w / 2
			, h
			, RGB(255, 0, 255));
	}

	if ((m_iIndex) == 2 || (m_iIndex) == 3)
	{
		vScale.x = vScale.x * 2.5f;
		vScale.y = vScale.y * 1.25f;
		TransparentBlt(_dc
			, (int)(vPos.x /*+ vScale.x / 4*/)
			, (int)(vPos.y /*+ vScale.y / 4*/)
			, (int)(vScale.x /*/ 2*/)
			, (int)(vScale.y /*/ 2*/)
			, m_pMissileTexture[m_iIndex]->GetDC()		///생성자에 있는 rand함수에 의해 m_iIndex가 0,1,2중 랜덤으로 정해진다
			, x
			, y
			, w
			, h / 2
			, RGB(255, 0, 255));
	}
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}

	if (pOtherObj->GetName() == L"Tile")
	{
		CTile* pTile;
		pTile = dynamic_cast<CTile*>(pOtherObj);
		if (pTile->GetTileType() == (UINT)TILE_TYPE::WALL)
		{
			DeleteObject(this);
		}
	}
}
