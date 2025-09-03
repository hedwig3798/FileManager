#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_Title.h"
#include "CEventMgr.h"
#include "CTrapTest.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		// 모든 씬이 모두 채워져 있는 것이 아니기 때문에 예외처리를 한다
		if (m_arrScene[i] != nullptr)
			delete m_arrScene[i];
	}

}

void CSceneMgr::Init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::TEST] = new CTrapTest;
	m_arrScene[(UINT)SCENE_TYPE::TEST]->SetName(L"Test Scene");

	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	m_arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Title Scene");

	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02;

	// 현재 씬 지정
	SetCurScene(m_arrScene[(UINT)SCENE_TYPE::TEST]);
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

// CEventMgr에서 이 함수가 실행된다
void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	SetCurScene(m_arrScene[(UINT)_eNext]);
	m_pCurScene->Enter();
}

