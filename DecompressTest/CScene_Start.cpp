#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Texture.h"
#include "CPathManager.h"
#include "CCollisionManager.h"

#include "CGameProcess.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CBoard.h"
#include "CEventMgr.h"

#include "SoundManager.h"
// 인게임 함정 오브젝트
#include "CTrap.h"
#include "CTrigger.h"
#include "CTrapArrow.h"
#include "CLever.h"
// IU 인게임 오브젝트 
#include "CMiniMap.h"
#include "CStone.h"
#include "CPoison.h"
#include "CPoisonCount.h"
#include "CClock.h"
#include "CClockConut.h"
#include "CPreferences.h"
#include "StageRelics.h"
#include "CDoor.h"
// Preferences의 패널 오브젝트
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CContinue.h"
#include "CReStart.h"
#include "CMainMenu.h"
// 인게임 몬스터 오브젝트
#include "CSpider.h"
#include "CGuardian.h"
#include "CTimeGuardian.h"

CScene_Start::CScene_Start(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_eNextScene = SCENE_TYPE::STAGE_1_1;
}

CScene_Start::~CScene_Start()
{
}

// 오브젝트 세팅
void CScene_Start::Enter(bool _isPast)
{
	SoundManager::GetInstance()->Play(SOUND::BACKGROUND_INGAME, SOUND_CHANNAL::BGM);

	m_bIsPast = false;
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetScale(Vector2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 1 ,5 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	StageRelics* pStageRelics = new StageRelics;
	pStageRelics->SetName(L"StageRelics");
	pStageRelics->SetPos(Vector2{ (BOARD_TILE / 2) + (BOARD_TILE * (BOARD_PENDING + 5)), (BOARD_TILE / 2) + (BOARD_TILE * (BOARD_PENDING + 1)) });
	pStageRelics->SetScale(Vector2(100.f, 100.f));
	pStageRelics->SetBoardPos(POINT{ 0 ,0 });
	AddObject(pStageRelics, GROUP_TYPE::RELICS);

	LoadTile(L"Tile\\S0\\Stage 0.tile", !m_bIsPast);
	LoadTile(L"Tile\\S0\\Stage 0.tile", m_bIsPast);

	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
}

bool CScene_Start::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();
	SoundManager::GetInstance()->Stop(EFFECT);
	// 충돌 매트릭스 체크 해제
	CCollisionManager::GetInstance()->Reset();
	m_iLoadedTileCount = 0;
	return m_bIsPast;
}
