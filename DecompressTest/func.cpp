#include "pch.h"
#include "func.h"
#include "CEventMgr.h"


// 오브젝트 생성 이벤트를 등록하는 함수입니다.
// 생성할 오브젝트의 주소와 오브젝트 타입을 매개 변수로 입력해주어야 합니다.
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInstance()->AddEvent(evn);
}

// 오브젝트 삭제 이벤트를 등록하는 함수입니다.
// 삭제할 오브젝트의 주소를 매개 변수로 입력해주어야 합니다.
void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInstance()->AddEvent(evn);
}

// 맵을 변경하는 이벤트를 등록하는 함수입니다.
// 맵을 변경할 맵의 타입을 매개 변수로 입력해주어야 합니다.
void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInstance()->AddEvent(evn);
}

// 트리거 발생하는 이벤트를 등록하는 함수입니다
void TriggerOn(CTile* _ptile)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::TRIGGER_ON;
	evn.lParam = (DWORD_PTR)_ptile;

	CEventMgr::GetInstance()->AddEvent(evn);
}

// 트리거 발생하는 이벤트를 등록하는 함수입니다
void LeverTriggerOn(CLever* _ptile)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::LEVERTRIGGER_ON;
	evn.lParam = (DWORD_PTR)_ptile;

	CEventMgr::GetInstance()->AddEvent(evn);
}

