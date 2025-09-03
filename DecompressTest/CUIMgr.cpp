#include "pch.h"
#include "CUIMgr.h"

#include "CSceneManager.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyManager.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{
 
}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	// 1. FocusedUI 확인 
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;
	CScene* pCurScene = CSceneManager::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);	

	bool bLbtnTap = CKeyManager::GetInstance()->GetKeyState(KEY::LBTN) == KEY_STATE::TAP;
	bool bLbtnAway = CKeyManager::GetInstance()->GetKeyState(KEY::LBTN) == KEY_STATE::AWAY;

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		// 부모 UI 포함, 자식 UI 들 중 실제 타켓팅 된 UI 해제된다.
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLbtnup();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				//왼쪽 버튼 떼면, 눌렷던 체크를 다시 해제한다.
				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneManager::GetInstance()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();
	bool bLbtnTap = CKeyManager::GetInstance()->GetKeyState(KEY::LBTN) == KEY_STATE::TAP;

	// 기존 포커싱을 UI를 받아두고 변경되었는 지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;
	if (bLbtnTap)
	{
		return pFocusedUI;
	}

	//왼쪽 버튼 Tap 이 발생했다는 전제.
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	//이번에 Focus 된 UI가 없다.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 백터내에서 맨뒤로 순번 교체 

	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱이 해체요청인 경우
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneManager::GetInstance()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// 백터내에서 맨뒤로 순번 교체 
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}



CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	
	bool bLbtnAway = CKeyManager::GetInstance()->GetKeyState(KEY::LBTN) == KEY_STATE::AWAY;
	
	//1. 부모 UI 포함, 모든 자식들을 검사한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기

		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI 인지 확인
		// 타켓 UI들 중, 더 우선 수위가 높은 기분은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild =  pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]); 
		}
	}

	// 왼쪽 버튼 떼면 눌럿던 체크를 다시 해제한다.
	if (bLbtnAway)
	{	
		for (size_t i = 0; i <vecNoneTarget.size(); ++i)
		{
		vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}
	// 2. 타켓 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI

	return pTargetUI;
}

void CUIMgr::ReStart()
{

}

void CUIMgr::Start()
{
}

void CUIMgr::MainMenu()
{

}



void CUIMgr::PlayerDio()
{

}

void CUIMgr::Continue()
{
}
