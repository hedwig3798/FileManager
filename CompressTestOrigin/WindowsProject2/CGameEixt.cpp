#include "pch.h"
#include "CScene.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

CGameEixt::CGameEixt()
	: m_iMousecheck(0)
{
	pEixt = TextureManager::GetInstance()->LoadTexture(L"Eixt1", L"texture\\quit_down.bmp");
	pEixtOn = TextureManager::GetInstance()->LoadTexture(L"Eixt2", L"texture\\quit_up.bmp");

	pNowEixt = pEixt;
}

CGameEixt::~CGameEixt()
{
	
}

void CGameEixt::MouseOn()
{

}

void CGameEixt::MouseLbtnDown()
{
	
}

void CGameEixt::MouseLbtnup()
{
	exit(0);
}

void CGameEixt::Render(HDC _dc)
{
	switch (m_iMousecheck)
	{
	case 0:
		 pNowEixt = pEixtOn;
		break;
	case 1:
		pNowEixt = pEixt;
		break;
	default:
		break;
	}

	int iWidth = (int)pNowEixt->Width();
	int iHeight = (int)pNowEixt->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x )
		, (int)(vPos.y )
		, iWidth, iHeight
		, pNowEixt->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CGameEixt::Update()
{
	if (IsMouseOn())
	{
		m_iMousecheck = 0;
	}
	else
	{
		m_iMousecheck = 1;
	}
}


