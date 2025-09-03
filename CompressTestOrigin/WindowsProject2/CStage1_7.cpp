#include "pch.h"
#include "CStage1_7.h"

CStage1_7::CStage1_7(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_1_8;
}

CStage1_7::~CStage1_7()
{

}

void CStage1_7::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 4 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	SetObject(GROUP_TYPE::LEVER, 5, 4, 5, true);
	SetObject(GROUP_TYPE::LEVER, 5, 4, 15, true);
	SetObject(GROUP_TYPE::LEVER, 5, 4, 5, false);
	SetObject(GROUP_TYPE::LEVER, 5, 4, 15, false);
	SetObject(GROUP_TYPE::LEVER, 10, 4, 5, false);

	LoadTile(L"Tile\\S1\\Stage 1 Room 7 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S1\\Stage 1 Room 7 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::TRIGGER, 1, 1, false);
	SetTrap(TILE_TYPE::FIRE, 0, 3, true);


	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage1_7::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
