#include "pch.h"
#include "CStone.h"
#include "Texture.h"
//#include "CResMgr.h"
#include "TextureManager.h"

#include "CKeyManager.h"
#include "CPathManager.h"


CStone::CStone(bool _isPast)
	: Pos(0)
	, m_bIsPast(_isPast)
{
	pStone1 = TextureManager::GetInstance()->LoadTexture(L"UIRelicsCur", L"texture\\relicOFF.bmp");
	pStone2 = TextureManager::GetInstance()->LoadTexture(L"UIRelicsPast", L"texture\\relicON.bmp");

}

CStone::~CStone()
{

}

void CStone::Update()
{
	// 과거랑 현재을 이동하는 키
	if (CKeyManager::GetInstance()->GetKeyState(KEY::C) == KEY_STATE::TAP)
	{
		m_bIsPast = !m_bIsPast;
	}

	
}

void CStone::Render(HDC _dc)
{
	if (m_bIsPast)
	{
		pNowStone = pStone1;
	}
	else
	{
		pNowStone = pStone2;
	}
	int iWidth = (int)pNowStone->Width();
	int iHeight = (int)pNowStone->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x + 60.f)
		, (int)(vPos.y -20.f)
		, iWidth, iHeight
		, pNowStone->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}
