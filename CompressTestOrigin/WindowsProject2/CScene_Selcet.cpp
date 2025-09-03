#include "pch.h"
#include "CScene_Selcet.h"
#include "CUI.h"
#include "TitleBackGround.h"
#include "StageBtn.h"
#include "Stage1_2Btn.h"
#include "Stage1_3Btn.h"
#include "Stage1_4Btn.h"
#include "Stage1_5Btn.h"
#include "Stage1_6Btn.h"
#include "Stage1_7Btn.h"
#include "Stage1_8Btn.h"
#include "Stage2_1Btn.h"

CScene_Selcet::CScene_Selcet(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{

}

CScene_Selcet::~CScene_Selcet()
{

}

void CScene_Selcet::Update()
{

}

void CScene_Selcet::Enter(bool _isPast)
{
	CObject* pBackground = new TitleBackGround;
	pBackground->SetName(L"BackGround");
	pBackground->SetScale(Vector2(1920, 1080));
	pBackground->SetPos(Vector2(0, 0));
	AddObject(pBackground, GROUP_TYPE::BACKGROUND);
	Vector2 vResoulution = Vector2(1920, 1080);
	Vector2 CountUI = Vector2(200.f, 200.f);

	SoundManager::GetInstance()->Stop(SOUND_CHANNAL::BGM);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CUI* pStage1_1Btn = new StageBtn(i, j);
			pStage1_1Btn->SetName(L"Stage1_1Btn");
			pStage1_1Btn->SetScale(Vector2(200.f, 200.f));
			pStage1_1Btn->SetPos(Vector2(vResoulution.x - (pStage1_1Btn->GetScale().x + 650.f - (j * 200)), 50.f + (i * 250)));
			AddObject(pStage1_1Btn, GROUP_TYPE::UI);
		}
	}

	// 

	// 	CUI* pStage1_2Btn = new Stage1_2Btn;
	// 	pStage1_2Btn->SetName(L"Stage1_3Btn");
	// 	pStage1_2Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_2Btn->SetPos(Vector2(vResoulution.x - (pStage1_2Btn->GetScale().x + 450.f), 50.f));
	// 	AddObject(pStage1_2Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage1_3Btn = new Stage1_3Btn;
	// 	pStage1_3Btn->SetName(L"Stage1_3Btn");
	// 	pStage1_3Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_3Btn->SetPos(Vector2(vResoulution.x - (pStage1_3Btn->GetScale().x + 250.f), 50.f));
	// 	AddObject(pStage1_3Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage1_4Btn = new Stage1_4Btn;
	// 	pStage1_4Btn->SetName(L"Stage1_4Btn");
	// 	pStage1_4Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_4Btn->SetPos(Vector2(vResoulution.x - (pStage1_4Btn->GetScale().x + 50.f), 50.f));
	// 	AddObject(pStage1_4Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage1_5Btn = new Stage1_5Btn;
	// 	pStage1_5Btn->SetName(L"Stage1_5Btn");
	// 	pStage1_5Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_5Btn->SetPos(Vector2(vResoulution.x - (pStage1_5Btn->GetScale().x + 650.f), 300.f));
	// 	AddObject(pStage1_5Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage1_6Btn = new Stage1_6Btn;
	// 	pStage1_6Btn->SetName(L"Stage1_6Btn");
	// 	pStage1_6Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_6Btn->SetPos(Vector2(vResoulution.x - (pStage1_6Btn->GetScale().x + 450.f), 300.f));
	// 	AddObject(pStage1_6Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage1_7Btn = new Stage1_7Btn;
	// 	pStage1_7Btn->SetName(L"Stage1_7Btn");
	// 	pStage1_7Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_7Btn->SetPos(Vector2(vResoulution.x - (pStage1_7Btn->GetScale().x + 250.f), 300.f));
	// 	AddObject(pStage1_7Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage1_8Btn = new Stage1_8Btn;
	// 	pStage1_8Btn->SetName(L"Stage1_8Btn");
	// 	pStage1_8Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage1_8Btn->SetPos(Vector2(vResoulution.x - (pStage1_8Btn->GetScale().x + 50.f), 300.f));
	// 	AddObject(pStage1_8Btn, GROUP_TYPE::UI);
	// 
	// 	CUI* pStage2_1Btn = new Stage2_1Btn;
	// 	pStage2_1Btn->SetName(L"Stage2_1Btn");
	// 	pStage2_1Btn->SetScale(Vector2(200.f, 200.f));
	// 	pStage2_1Btn->SetPos(Vector2(vResoulution.x - (pStage2_1Btn->GetScale().x + 650.f), 550.f));
	// 	AddObject(pStage2_1Btn, GROUP_TYPE::UI);
}

bool CScene_Selcet::Exit()
{
	SoundManager::GetInstance()->Stop(EFFECT);
	DeleteAll();
	return false;
}

