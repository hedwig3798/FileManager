#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CTile.h"
#include "CLever.h"
#include "CSceneManager.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	// ============================================
	// 이전 프레임에서 등록해둔 Dead Object들을 삭제한다
	// ============================================
	for (auto obj : m_vecDead)
	{
		delete obj;
	}
	//for (size_t i = 0; i < m_vecDead.size(); i++)
	//{
	//	delete m_vecDead[i];
	//}
	m_vecDead.clear();

	// ==========
	// Evnet 처리
	// ==========

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

// func.cpp에서 등록한 이벤트들이 처리됩니다
void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneManager::GetInstance()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	// 바로 삭제하면 다음 프레임에서 해당 오브젝트를 참조 하고 있던 객체들은 없는 메모리에 접근하기 때문에
	// 해당 이벤트에서 다음 프레임에서 삭제할 예정이라고 다른 객체에 알려주어야 한다
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.insert(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
		CSceneManager::GetInstance()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	case EVENT_TYPE::TRIGGER_ON:
	{
		CTile* pTriggerTile = (CTile*)_eve.lParam;
		CSceneManager::GetInstance()->GetCurScene()->TriggerEvent(pTriggerTile->GetTriggerNumber(), GROUP_TYPE::TILE);
	}
	break;
	case EVENT_TYPE::LEVERTRIGGER_ON:
	{
		CLever* pLever = (CLever*)_eve.lParam;
		CSceneManager::GetInstance()->GetCurScene()->TriggerEvent(pLever->GetTriggerNumber(), GROUP_TYPE::LEVER);
	}
		break;
	default:
		break;
	}
}
