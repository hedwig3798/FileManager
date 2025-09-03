#include "pch.h"
#include "CStage2_4.h"

CStage2_4::CStage2_4(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_2_5;
}

CStage2_4::~CStage2_4()
{

}

void CStage2_4::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,3 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	SetMonster(MONSTER_TYPE::GUARDIAN, 5, 6, m_bIsPast, 0, true, false);
	SetMonster(MONSTER_TYPE::GUARDIAN, 5, 3, m_bIsPast, 0, true, false);
 	SetMonster(MONSTER_TYPE::GUARDIAN, 9, 6, m_bIsPast, 0, true, false);
 	SetMonster(MONSTER_TYPE::GUARDIAN, 9, 3, m_bIsPast, 0, true, false);
	SetObject(GROUP_TYPE::LEVER, 1, 5, 6, true);
	SetObject(GROUP_TYPE::LEVER, 1, 5, 17, true);
	SetObject(GROUP_TYPE::LEVER, 1, 7, 8, true);
	SetObject(GROUP_TYPE::LEVER, 1, 7, 15, true);
	SetObject(GROUP_TYPE::LEVER, 13, 5, 9, true);
	SetObject(GROUP_TYPE::LEVER, 13, 5, 18, true);
	SetObject(GROUP_TYPE::LEVER, 13, 3, 7, true);
	SetObject(GROUP_TYPE::LEVER, 13, 3, 16, true);


	LoadTile(L"Tile\\S2\\s2-4 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S2\\s2-4 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::FIRE, 4, 16, true);

	SetDefaultCollision();

	SetUI(m_bIsPast);
}

bool CStage2_4::Exit()
{
	// 모든 오브젝트 삭제	
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
