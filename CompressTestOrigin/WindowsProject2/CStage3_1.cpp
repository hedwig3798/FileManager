#include "pch.h"
#include "CStage3_1.h"

CStage3_1::CStage3_1(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_3_2;
}

CStage3_1::~CStage3_1()
{

}

void CStage3_1::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 0 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	LoadTile(L"Tile\\S3\\Stage 3 Room 1 Present.tile", !m_bIsPast);
	LoadTile(L"Tile\\S3\\Stage 3 Room 1 Past.tile", m_bIsPast);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage3_1::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
