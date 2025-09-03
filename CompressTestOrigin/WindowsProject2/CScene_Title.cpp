#include "pch.h"
#include "CScene_Title.h"
#include "CObject.h"
//#include "CResMgr.h"
#include "TextureManager.h"


#include "CUI.h"
#include "CGameStart.h"
#include "CStageSelcet.h"
#include "CGameEixt.h"
#include "CLogo.h"

#include "CPanelExit.h"
#include "CEixtNoBtn.h"
#include "CEixtYesBtn.h"
#include "TitleBackGround.h"
#include "SoundManager.h"

CScene_Title::CScene_Title(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
	
{
	m_eNextScene = SCENE_TYPE::START;
}

CScene_Title::~CScene_Title()
{

}

void CScene_Title::Update()
{
	CScene::Update();


}

void CScene_Title::Enter(bool _isPast)
{
	SoundManager::GetInstance()->Stop(BGM);
	SoundManager::GetInstance()->Play(BACKGROUND_MAINTITLE, BGM);

	/// 전체 해상도 크기
	Vector2 vResoulution = Vector2{ 1920, 1080 };
	
	/// 배경화면 
	CObject* pBackground = new TitleBackGround;
	pBackground->SetName(L"BackGround");
	pBackground->SetScale(Vector2(1920, 1080));
	pBackground->SetPos(Vector2(0, 0));
	AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	/// 제목 
	CUI* pLogo = new CLogo;
	pLogo->SetName(L"Logo");
	pLogo->SetScale(Vector2(700.f, 300.f));
	pLogo->SetPos(Vector2((vResoulution.x) - (pLogo->GetScale().x + 50.f), 50.f));
	AddObject(pLogo, GROUP_TYPE::UI);
	
	///연습용 제목
// 	CUI* pTestLogo = new Test_Logo;
// 	pTestLogo->SetName(L"Test_Logo");
// 	pTestLogo->SetScale(Vector2(300.f, 300.f));
// 	pTestLogo->SetPos(Vector2((vResoulution.x) - (pLogo->GetScale().x + 350.f), 50.f));
// 	AddObject(pTestLogo, GROUP_TYPE::UI);
	
	/// 시작 버튼
	Vector2 MainBtn = Vector2(400.f, 150.f);
	CUI* pGameStart = new CGameStart;
	pGameStart->SetName(L"GameStart");
	pGameStart->SetScale(MainBtn);
	pGameStart->SetPos(Vector2((vResoulution.x) - (pGameStart->GetScale().x + 300.f), 550.f));
	AddObject(pGameStart, GROUP_TYPE::UI);
	/// 스테이지 선택 버튼
	CUI* pStageSelcet = new CStageSelcet;
	pStageSelcet->SetName(L"StageSelcet");
	pStageSelcet->SetScale(MainBtn);
	pStageSelcet->SetPos(Vector2((vResoulution.x) - (pStageSelcet->GetScale().x + 300.f), 700.f));
	AddObject(pStageSelcet, GROUP_TYPE::UI);
	
	/// 나가기 
	CUI* pGameEixt = new CGameEixt;
	pGameEixt->SetName(L"GameEixt");
	pGameEixt->SetScale(MainBtn);
	pGameEixt->SetPos(Vector2((vResoulution.x) - (pGameEixt->GetScale().x + 300.f), 850.f));
	AddObject(pGameEixt, GROUP_TYPE::UI);


}


bool CScene_Title::Exit()
{
	SoundManager::GetInstance()->Stop(BGM);
	SoundManager::GetInstance()->Stop(EFFECT);
	DeleteAll();
	return false;
}
