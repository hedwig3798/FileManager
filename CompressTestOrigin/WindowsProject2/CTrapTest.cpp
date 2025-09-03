#include "pch.h"
#include "CTrapTest.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Texture.h"
#include "CPathManager.h"
#include "CCollisionManager.h"

#include "CGameProcess.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CBoard.h"
#include "CEventMgr.h"

#include "SoundManager.h"
#include "CTrap.h"
#include "CTrigger.h"
#include "CTrapArrow.h"

#include "CSpider.h"
#include "CGuardian.h"
#include "CTimeGuardian.h"
CTrapTest::CTrapTest(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{

}

CTrapTest::~CTrapTest()
{

}
void CTrapTest::Update()
{
	// 부모쪽 update()함수를 호출
	CScene::Update();

	if (CKeyManager::GetInstance()->GetKeyState(KEY::ENTER) == KEY_STATE::TAP)
	{
		// 이벤트 등록
		ChangeScene(SCENE_TYPE::TOOL);
	}



	if (CKeyManager::GetInstance()->GetKeyState(KEY::C) == KEY_STATE::TAP)
	{
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::MONSTER].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::MONSTER][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::MONSTER][i]->m_bActive;
		}
	}
}

void CTrapTest::Enter(bool _isPast)
{
	// 플레이어 추가
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vector2{ (BOARD_TILE / 2) + (BOARD_TILE * 3), BOARD_TILE / 2 });
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 0 ,0 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	LoadTile(L"Tile\\TrapTest.tile", true);

	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_ABSOLUTE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TRAP_ARROW);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TRAP_FIRE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER_ABSOLUTE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_MONSTER, GROUP_TYPE::PLAYER);
}

bool CTrapTest::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();

	return m_bIsPast;
}


