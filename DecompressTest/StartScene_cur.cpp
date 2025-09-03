#include "pch.h"
#include "StartScene_cur.h"
#include "CEventMgr.h"
#include "CKeyMgr.h"
StartScene_cur::StartScene_cur()
{

}

StartScene_cur::~StartScene_cur()
{

}


void StartScene_cur::update()
{
	CScene::update();
	if (KEY_TAP(KEY::Z))
	{
		CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::SCENE_SWAP, (DWORD_PTR)this, (DWORD_PTR)SCENE_TYPE::START_PRE });
	}
}

void StartScene_cur::Enter()
{

}

void StartScene_cur::Exit()
{

}

