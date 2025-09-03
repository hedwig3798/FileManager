#include "pch.h"
#include "CStage2_2.h"

CStage2_2::CStage2_2(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_2_3;
}

CStage2_2::~CStage2_2()
{

}

void CStage2_2::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 3 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	SetMonster(MONSTER_TYPE::GUARDIAN, 5, 2, m_bIsPast, 0, true, false);
	SetMonster(MONSTER_TYPE::GUARDIAN, 7, 2, m_bIsPast, 0, true, false);
	SetMonster(MONSTER_TYPE::GUARDIAN, 9, 2, m_bIsPast, 0, true, false);
	SetMonster(MONSTER_TYPE::GUARDIAN, 6, 2, m_bIsPast, 0, true, false);
	SetMonster(MONSTER_TYPE::GUARDIAN, 8, 2, m_bIsPast, 0, true, false);
	SetMonster(MONSTER_TYPE::GUARDIAN, 10, 2, m_bIsPast, 0, true, false);

	LoadTile(L"Tile\\S2\\Stage2 Room 2 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S2\\Stage2 Room 2 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::FIRE, 0, 16, true);
	SetTrap(TILE_TYPE::TRIGGER, 0, 16, true);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage2_2::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
