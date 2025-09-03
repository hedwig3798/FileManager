#include "pch.h"
#include "CStage2_6.h"

CStage2_6::CStage2_6(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_3_1;
}

CStage2_6::~CStage2_6()
{

}

void CStage2_6::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = true;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	LoadTile(L"Tile\\S2\\s2-6 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S2\\s2-6 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::FIRE, 0, 16, true);
	SetTrap(TILE_TYPE::TRIGGER, 0, 16, true);

	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 5, 3, true);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 5, 7, true);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 7, 3, true);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 7, 7, true);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 9, 3, true);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 9, 7, true);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage2_6::Exit()
{
	// 모든 오브젝트 삭제	
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
