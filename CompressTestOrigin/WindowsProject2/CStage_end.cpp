#include "pch.h"
#include "CStage_end.h"

CStage_end::CStage_end(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::ENDING;
}

CStage_end::~CStage_end()
{

}

void CStage_end::Enter(bool _isPast)
{
	// 플레이어 추가
	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,4 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	StageRelics* pStageRelics = new StageRelics;
	pStageRelics->SetName(L"StageRelics");
	pStageRelics->SetPos(Vector2{ (BOARD_TILE / 2) + (BOARD_TILE * (BOARD_PENDING + 5)), (BOARD_TILE / 2) + (BOARD_TILE * (BOARD_PENDING + 1)) });
	pStageRelics->SetScale(Vector2(100.f, 100.f));
	pStageRelics->SetBoardPos(POINT{ 0 ,0 });
	AddObject(pStageRelics, GROUP_TYPE::RELICS);

	LoadTile(L"Tile\\end\\stage_4.tile", !m_bIsPast);
	LoadTile(L"Tile\\end\\stage_4.tile", m_bIsPast);

	SetDefaultCollision();
	SetUI(m_bIsPast);
}

bool CStage_end::Exit()
{
	SoundManager::GetInstance()->Stop(BGM);
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
