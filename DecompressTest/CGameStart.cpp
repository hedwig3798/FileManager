#include "pch.h"
#include "CGameStart.h"
#include "TextureManager.h"

CGameStart::CGameStart()
	: m_iMousecheck(0)
{
	pGamestart = TextureManager::GetInstance()->LoadTexture(L"Start", L"texture\\new_down.bmp");
	pGamestarton = TextureManager::GetInstance()->LoadTexture(L"Start1", L"texture\\new_up.bmp");
	
	pNowgame = pGamestart;
}

CGameStart::~CGameStart()
{

}

void CGameStart::MouseOn()
{

}

void CGameStart::MouseLbtnDown()
{

}

void CGameStart::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::CUTSCENE);
}

void CGameStart::Render(HDC _dc)
{
	switch (m_iMousecheck)
	{
	case 0: 
		pNowgame = pGamestarton;
		break;
	case 1:
		pNowgame = pGamestart;
		break;
	default:
		break;
	}

	int iWidth = (int)pNowgame->Width();
	int iHeight = (int)pNowgame->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x )
		, (int)(vPos.y )
		, iWidth, iHeight
		, pNowgame->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CGameStart::Update()
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
