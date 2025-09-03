#include "pch.h"
#include "CStage2_5.h"

CStage2_5::CStage2_5(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_2_6;
}

CStage2_5::~CStage2_5()
{

}

void CStage2_5::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 1, 3, false);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 1, 4, false);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 1, 5, false);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 1, 6, false);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 1, 7, false);


	SetObject(GROUP_TYPE::LEVER, 2, 5, 15, true);
	SetObject(GROUP_TYPE::LEVER, 9, 3, 17, false);
	SetObject(GROUP_TYPE::LEVER, 9, 7, 1, false);
	SetObject(GROUP_TYPE::LEVER, 12, 3, 16, false);
	SetObject(GROUP_TYPE::LEVER, 12, 7, 1, false);

	LoadTile(L"Tile\\S2\\Stage 2 Room 5 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S2\\Stage 2 Room 5 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::FIRE, 0, 20, true);
	SetTrap(TILE_TYPE::TRIGGER, 0, 16, false);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage2_5::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
