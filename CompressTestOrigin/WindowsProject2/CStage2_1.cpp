#include "pch.h"
#include "CStage2_1.h"

CStage2_1::CStage2_1(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_2_2;
}

CStage2_1::~CStage2_1()
{

}

void CStage2_1::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	SetMonster(MONSTER_TYPE::GUARDIAN, 3, 3, m_bIsPast, 2, true);
	SetMonster(MONSTER_TYPE::GUARDIAN, 7, 7, m_bIsPast, 2, true);
	SetMonster(MONSTER_TYPE::GUARDIAN, 12, 4, m_bIsPast, 2, true);

	LoadTile(L"Tile\\S2\\Stage 2 Room 1 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S2\\Stage 2 Room 1 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::FIRE, 0, 16, true);
	SetTrap(TILE_TYPE::TRIGGER, 0, 16, true);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage2_1::Exit()
{
	// 모든 오브젝트 삭제	
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
