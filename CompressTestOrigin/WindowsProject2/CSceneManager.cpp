#include "pch.h"
#include "CSceneManager.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_Selcet.h"
#include "CEventMgr.h"
#include "CScene_Title.h"
#include "CCutScene.h"
#include "CEndSCene.h"
#include "Stages.h"

CSceneManager::CSceneManager()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{

}

CSceneManager::~CSceneManager()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		// 모든 씬이 모두 채워져 있는 것이 아니기 때문에 예외처리를 한다
		if (m_arrScene[i] != nullptr)
			delete m_arrScene[i];
	}

}

void CSceneManager::Initialize(HWND hWnd, HDC hDC, POINT screenRes)
{
	// Scene 로딩
#pragma region testing
	// 테스트용 씬
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::START]->m_eNowScene = SCENE_TYPE::START;
#pragma endregion

	m_arrScene[(UINT)SCENE_TYPE::SELCETMAP] = new CScene_Selcet(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::SELCETMAP]->SetName(L"Select Scene");
	m_arrScene[(UINT)SCENE_TYPE::SELCETMAP]->m_eNowScene = SCENE_TYPE::SELCETMAP;
#pragma region title
	// 타이틀, 오프닝, 엔딩
	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->m_eNowScene = SCENE_TYPE::TITLE;

	m_arrScene[(UINT)SCENE_TYPE::CUTSCENE] = new CCutScene(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::CUTSCENE]->SetName(L"Cut Scene");
	m_arrScene[(UINT)SCENE_TYPE::CUTSCENE]->m_eNowScene = SCENE_TYPE::CUTSCENE;

	m_arrScene[(UINT)SCENE_TYPE::ENDING] = new CEndSCene(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::ENDING]->SetName(L"Ending Scene");
	m_arrScene[(UINT)SCENE_TYPE::ENDING]->m_eNowScene = SCENE_TYPE::ENDING;
#pragma endregion

#pragma region stage1
	// 스테이지 1
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_1] = new CStage1_1(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_1]->SetName(L"Stage 1-1");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_1]->m_eNowScene = SCENE_TYPE::STAGE_1_1;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_2] = new CStage1_2(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_2]->SetName(L"Stage 1-2");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_2]->m_eNowScene = SCENE_TYPE::STAGE_1_2;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_3] = new CStage1_3(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_3]->SetName(L"Stage 1-3");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_3]->m_eNowScene = SCENE_TYPE::STAGE_1_3;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_5] = new CStage1_5(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_5]->SetName(L"Stage 1-5");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_5]->m_eNowScene = SCENE_TYPE::STAGE_1_5;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_6] = new CStage1_6(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_6]->SetName(L"Stage 1-6");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_6]->m_eNowScene = SCENE_TYPE::STAGE_1_6;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_7] = new CStage1_7(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_7]->SetName(L"Stage 1-7");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_7]->m_eNowScene = SCENE_TYPE::STAGE_1_7;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_8] = new CStage1_8(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_8]->SetName(L"Stage 1-8");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_1_8]->m_eNowScene = SCENE_TYPE::STAGE_1_8;
#pragma endregion

#pragma region stage2
	// 스테이지 2
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_1] = new CStage2_1(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_1]->SetName(L"Stage 2-1");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_1]->m_eNowScene = SCENE_TYPE::STAGE_2_1;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_2] = new CStage2_2(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_2]->SetName(L"Stage 2-2");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_2]->m_eNowScene = SCENE_TYPE::STAGE_2_2;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_3] = new CStage2_3(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_3]->SetName(L"Stage 2-3");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_3]->m_eNowScene = SCENE_TYPE::STAGE_2_3;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_4] = new CStage2_4(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_4]->SetName(L"Stage 2-4");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_4]->m_eNowScene = SCENE_TYPE::STAGE_2_4;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_5] = new CStage2_5(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_5]->SetName(L"Stage 2-5");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_5]->m_eNowScene = SCENE_TYPE::STAGE_2_5;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_6] = new CStage2_6(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_6]->SetName(L"Stage 2-6");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_2_6]->m_eNowScene = SCENE_TYPE::STAGE_2_6;
#pragma endregion

#pragma region stage3
	// 스테이지 3
	m_arrScene[(UINT)SCENE_TYPE::STAGE_3_1] = new CStage3_1(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_3_1]->SetName(L"Stage 3-1");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_3_1]->m_eNowScene = SCENE_TYPE::STAGE_3_1;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_3_2] = new CStage3_2(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_3_2]->SetName(L"Stage 3-2");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_3_2]->m_eNowScene = SCENE_TYPE::STAGE_3_2;
#pragma endregion

#pragma region end
	m_arrScene[(UINT)SCENE_TYPE::STAGE_END] = new CStage_end(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::STAGE_END]->SetName(L"Stage 3-1");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_END]->m_eNowScene = SCENE_TYPE::STAGE_END;
#pragma endregion

	m_arrScene[(UINT)SCENE_TYPE::CREDIT] = new CCredit(hWnd, hDC, screenRes);
	m_arrScene[(UINT)SCENE_TYPE::CREDIT]->SetName(L"CREDIT");
	m_arrScene[(UINT)SCENE_TYPE::CREDIT]->m_eNowScene = SCENE_TYPE::CREDIT;

	// 현재 씬 지정
	SetCurScene(m_arrScene[(UINT)SCENE_TYPE::TITLE]);

	m_pCurScene->Enter(false);
}

void CSceneManager::Update()
{
	m_pCurScene->Update();

	m_pCurScene->Finalupdate();
}

void CSceneManager::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

// CEventMgr에서 이 함수가 실행된다
void CSceneManager::ChangeScene(SCENE_TYPE _eNext)
{
	bool isPast = m_pCurScene->Exit();
	SetCurScene(m_arrScene[(UINT)_eNext]);
	m_pCurScene->Enter(isPast);
}

