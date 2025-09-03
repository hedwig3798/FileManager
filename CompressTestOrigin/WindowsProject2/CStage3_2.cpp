#include "pch.h"
#include "CStage3_2.h"

CStage3_2::CStage3_2(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_END;
}

CStage3_2::~CStage3_2()
{

}

void CStage3_2::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = true;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);


	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 3 - 3, 4, true);
	SetMonster(MONSTER_TYPE::TIMEGUARDIAN, 7 - 4, 4, true);
	LoadTile(L"Tile\\S3\\s3-2 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S3\\s3-2 Past.tile", m_bIsPast);

	SetTrap(TILE_TYPE::FIRE, 0, 3, true);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage3_2::Exit()
{
	
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
