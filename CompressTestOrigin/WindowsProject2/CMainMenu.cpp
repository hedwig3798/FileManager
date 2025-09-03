#include "pch.h"
#include "CMainMenu.h"
#include "TextureManager.h"
#include "CScene.h"


CMainMenu::CMainMenu():
	m_iMousecheck(0)
{
	pMainMenu = TextureManager::GetInstance()->LoadTexture(L"MainMenu", L"texture\\iconDead.bmp");
	pMainMenuOn = TextureManager::GetInstance()->LoadTexture(L"pMainMenuOn", L"texture\\stageselect_on.bmp");

	pNowMainMenu = pMainMenu;
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::MouseOn()
{
}

void CMainMenu::MouseLbtnDown()
{

}

void CMainMenu::MouseLbtnup()
{
	
	ChangeScene(SCENE_TYPE::TITLE);
}

void CMainMenu::Render(HDC _dc)
{
	switch (m_iMousecheck)
	{
	case 0:
		pNowMainMenu = pMainMenu;
		break;
	case 1:
		pNowMainMenu = pMainMenuOn;
		break;
	default:
		break;
	}

	int iWidth = (int)pNowMainMenu->Width();
	int iHeight = (int)pNowMainMenu->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x )
		, (int)(vPos.y )
		, iWidth, iHeight
		, pNowMainMenu->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CMainMenu::Update()
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
