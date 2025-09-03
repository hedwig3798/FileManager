#include "pch.h"
#include "CPreferences.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CContinue.h"
#include "CReStart.h"
#include "CMainMenu.h"
#include "CObject.h"
#include "CScene.h"
#include "TextureManager.h"
class CObject;

CPreferences::CPreferences()
{
	Preferences = TextureManager::GetInstance()->LoadTexture(L"iconPer", L"texture\\iconPer.bmp");
	
// 	Vector2 vResoulution = Vector2(1920, 1080);
// 	Vector2 pUIScale = Vector2(450.f, 600.f);
// 	Vector2 pchildUI = Vector2(200.f, 100.f);
// 
// 	pPanelUI = new CPanelUI;
// 	pPanelUI->m_bActive = false;
// 	pPanelUI->SetName(L"ParentUI");
// 	pPanelUI->SetScale(pUIScale);
// 	pPanelUI->SetPos(Vector2(
// 		(vResoulution.x / 2) - (pPanelUI->GetScale().x / 2),
// 		(vResoulution.y / 2) - (pPanelUI->GetScale().y / 2)));
// 
// 	CUI* pBtnUI = new CBtnUI;
// 	pBtnUI->SetName(L"CBtn");
// 	pBtnUI->SetScale(Vector2(300.f, 100.f));
// 	pBtnUI->SetPos(Vector2(
// 		(pUIScale.x / 2) - (pBtnUI->GetScale().x / 2),
// 		(pUIScale.y / 5) - (pBtnUI->GetScale().y / 2)));
// 
// 	CUI* pContinue = new CContinue;
// 	pContinue->SetName(L"ContinueBtn");
// 	pContinue->SetScale(Vector2(pchildUI));
// 	pContinue->SetPos(Vector2(
// 		(pUIScale.x / 2) - (pContinue->GetScale().x / 2),
// 		(pUIScale.y * 2 / 5) - (pContinue->GetScale().y / 2)));
// 
// 	CUI* pCRestart = new CReStart;
// 	pCRestart->SetName(L"ReStartBtn");
// 	pCRestart->SetScale(pchildUI);
// 	pCRestart->SetPos(Vector2(
// 		(pUIScale.x / 2) - (pCRestart->GetScale().x / 2),
// 		(pUIScale.y * 3 / 5) - (pCRestart->GetScale().y / 2)));
// 
// 	CUI* pMainMenu = new CMainMenu;
// 	pMainMenu->SetName(L"CMainMenuBtn");
// 	pMainMenu->SetScale(pchildUI);
// 	pMainMenu->SetPos(Vector2(
// 		(pUIScale.x / 2) - (pMainMenu->GetScale().x / 2),
// 		(pUIScale.y * 4 / 5) - (pMainMenu->GetScale().y / 2)));
// 	pPanelUI->AddChild(pBtnUI);
// 	pPanelUI->AddChild(pContinue);
// 	pPanelUI->AddChild(pCRestart);
// 	pPanelUI->AddChild(pMainMenu);
// 	CreateObject(pPanelUI, GROUP_TYPE::PANEL_UI);
	

}

CPreferences::~CPreferences()
{
}

void CPreferences::MouseOn()
{

}

void CPreferences::MouseLbtnDown()
{
	ChangeScene(SCENE_TYPE::TITLE);
	SoundManager::GetInstance()->Stop(BGM);
	//pPanelUI->m_bActive = !pPanelUI->m_bActive;
}

void CPreferences::MouseLbtnup()
{
	
}

void CPreferences::Update()
{

}

void CPreferences::Render(HDC _dc)
{
	int iWidth = (int)Preferences->Width();
	int iHeight = (int)Preferences->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(
		_dc
		, (int)(vPos.x )
		, (int)(vPos.y )
		, iWidth, iHeight
		, Preferences->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));
}

