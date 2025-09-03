#include "pch.h"
#include "CStage1_3.h"

CStage1_3::CStage1_3(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_1_5;
}

CStage1_3::~CStage1_3()
{

}

void CStage1_3::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = true;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,4 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	LoadTile(L"Tile\\S1\\Stage1 Room 3 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S1\\Stage 1 Room 3 Past.tile", m_bIsPast);
	
	SetUI(m_bIsPast);
	SetDefaultCollision();
}

bool CStage1_3::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
