#include "pch.h"
#include "CStage1_8.h"

CStage1_8::CStage1_8(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_2_1;
}

CStage1_8::~CStage1_8()
{

}

void CStage1_8::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 2 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	LoadTile(L"Tile\\S1\\Stage1 Room 8 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S1\\Stage1 Room 8 Past.tile", m_bIsPast);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage1_8::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
