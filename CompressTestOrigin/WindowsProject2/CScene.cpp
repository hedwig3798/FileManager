#include "pch.h"
#include "CScene.h"

//#include "CResMgr.h"
#include "TextureManager.h"

#include "CPathManager.h"
#include "CSceneManager.h"

#include "CObject.h"
#include "CTile.h"
#include "CLever.h"
#include "CPlayer.h"
#include "CDoor.h"
#include "CThron.h"
#include "CFire.h"

#include "CCollisionManager.h"

#include <stdio.h>

#include "CSpider.h"
#include "CGuardian.h"
#include "CTimeGuardian.h"
#include "CKeyManager.h"

CScene::CScene(HWND hWnd, HDC hDC, POINT screenRes)
	: m_iTileX(0)
	, m_iTileY(0)
	, m_iTileTypeNumber(1)
	, m_hWnd(hWnd)
	, m_hDC(hDC)
	, m_screenRes(screenRes)
	, m_bIsPast(false)
	, m_iLoadedTileCount(0)
	, CollisionVisible(true)
	, m_eNextScene(SCENE_TYPE::TITLE)
	, m_eNowScene(SCENE_TYPE::TITLE)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
		{
			// m_arrObj[i] 그룹 백터의 j물체 삭제
			delete m_arrObj[i][j];
		}
	}
}

// 모든 오브젝트 update하기 단 Dead상태일 경우 EventMgr에서 다음 프레임에서 제거하기 때문에 그려주지 않는다
void CScene::Update()
{
	if (CKeyManager::GetInstance()->GetKeyState(KEY::C) == KEY_STATE::TAP)
	{
		SoundManager::GetInstance()->Play(SOUND::PLAYER_DEAD, SOUND_CHANNAL::EFFECT);

		m_bIsPast = !m_bIsPast;
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::MONSTER].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::MONSTER][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::MONSTER][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::TILE].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::TILE][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::TILE][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::PROJ_MONSTER].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::PROJ_MONSTER][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::PROJ_MONSTER][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::TRAP_ARROW].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::TRAP_ARROW][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::TRAP_ARROW][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::TRAP_FIRE].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::TRAP_FIRE][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::TRAP_FIRE][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::TILE_APPERENCE].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::TILE_APPERENCE][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::TILE_APPERENCE][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::LEVER].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::LEVER][i]->m_bActive = !m_arrObj[(UINT)GROUP_TYPE::LEVER][i]->m_bActive;
		}
		for (size_t i = 0; i < m_arrObj[(UINT)GROUP_TYPE::MONSTER_ABSOLUTE].size(); i++)
		{
			m_arrObj[(UINT)GROUP_TYPE::MONSTER_ABSOLUTE][i]->m_bActive = true;
		}
	}
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
				continue;
			}
			else if (!(*iter)->m_bActive)
			{
				iter++;
			}
			else
			{
				(*iter)->Update();
				iter++;
			}
		}
	}

	// 키를 누르면 개발자 모드 함수 실행 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::N_1) == KEY_STATE::TAP)
	{
		DeveloperMode(1);
	}
	if (CKeyManager::GetInstance()->GetKeyState(KEY::N_2) == KEY_STATE::TAP)
	{
		DeveloperMode(2);
	}
	if (CKeyManager::GetInstance()->GetKeyState(KEY::N_3) == KEY_STATE::TAP)
	{
		DeveloperMode(3);
	}

}

void CScene::Finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->Finalupdate();
		}
	}
}

// 모든 오브젝트 그려주기 단 Dead상태일 경우 EventMgr에서 다음 프레임에서 제거하기 때문에 그려주지 않는다
void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j]->IsDead())
			{
				continue;
			}
			if (!m_arrObj[i][j]->m_bActive)
			{
				continue;
			}
			if (i == (UINT)GROUP_TYPE::TRAP_FIRE)
			{
				CFire* pFire = (CFire*)m_arrObj[i][j];
				if (pFire->TriggerOn == false)
					continue;
			}
			m_arrObj[i][j]->Render(_dc);
			m_arrObj[i][j]->ComponentRender(_dc, !CollisionVisible);
		}
	}

}

// 타일만 렌더링 따로 해주기 ( 추가 : 이건재 )
void CScene::TriggerEvent(int _TileTriggerNumber, GROUP_TYPE _ObjectType)
{
	if (_TileTriggerNumber >= 21)
	{
		vector<CObject*>::iterator iter = m_arrObj[(UINT)GROUP_TYPE::DOOR].begin();

		for (; iter != m_arrObj[(UINT)GROUP_TYPE::DOOR].end(); iter++)
		{
			CDoor* pDoor;
			pDoor = (CDoor*)(*iter);

			pDoor->SetDoor();
		}
	}


	vector<CObject*>::iterator iter = m_arrObj[(UINT)GROUP_TYPE::TILE].begin();

	for (; iter != m_arrObj[(UINT)GROUP_TYPE::TILE].end(); iter++)
	{
		CTile* tile;
		tile = (CTile*)(*iter);

		tile->TriggerOn(_TileTriggerNumber, _ObjectType);
	}
}

// 개발자 모드 On ( 1은 Collision 보이기, 2는 Collision 끄기 )
void CScene::DeveloperMode(int ModeType)
{
	if (ModeType == 1)
	{
		if (CollisionVisible)
		{
			CollisionVisible = false;
		}
		else
		{
			CollisionVisible = true;
		}

	}
	else if (ModeType == 2)
	{
		vector<CObject*>::iterator iter = m_arrObj[(UINT)GROUP_TYPE::PLAYER].begin();

		for (; iter != m_arrObj[(UINT)GROUP_TYPE::PLAYER].end(); iter++)
		{
			CPlayer* Player;
			Player = (CPlayer*)(*iter);


			if (Player->m_CollisionOn)
				Player->m_CollisionOn = false;
			else
				Player->m_CollisionOn = true;
		}
	}
	else if (ModeType == 3)
	{
		ChangeScene(m_eNextScene);
	}
}

// 모든 오브젝트 삭제하기
void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>
		(m_arrObj[(UINT)_eTarget]);
}

// 모든 오브젝트 삭제하기
void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}


// 타일 생성하기 함수 ( 추가 : 이건재 )
void CScene::CreateTile(UINT _iXCount, UINT _iYCount, UINT _TileFileNumber, bool _activate)
{
	int Width = 0;

	// 에디터 툴로 넘어갈 때, 기존 타일 오브젝트를 삭제
	// 다른 씬이라면 타일들을 오른쪽으로 BOARD_TILE * 3만큼 이동
	if (CSceneManager::GetInstance()->GetCurScene()->GetName() == L"Tool Scene")
		DeleteGroup(GROUP_TYPE::TILE);
	//else
	//	Width = BOARD_TILE * 3;

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;
	m_iTileTypeNumber = _TileFileNumber;

	// 타일 파일 넘버에 따라서 가져오는 텍스쳐 파일 변경
	wstring TileFileNum = L"texture\\Tile\\Tile";
	TileFileNum += (wchar_t)(m_iTileTypeNumber + '0');
	TileFileNum += L".bmp";

	wstring TileName = L"Tile";
	TileName += (wchar_t)(m_iTileTypeNumber + '0');

	//Texture* pTileTex = CResMgr::GetInstance()->LoadTexture(TileName, TileFileNum);
	Texture* pTileTex = TextureManager::GetInstance()->LoadTexture(TileName, TileFileNum);

	// 타일 생성, .tile 파일 로드된 
	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			CTile* pTile = new CTile(m_hDC);

			pTile->SetPos(Vector2((float)(j * BOARD_TILE + Width), (float)(i * BOARD_TILE)));
			pTile->SetScale(Vector2(BOARD_TILE, BOARD_TILE));
			pTile->SetTexture(pTileTex);
			pTile->m_bActive = _activate;

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

// 타일 불러오기 함수 ( 추가 : 이건재 )
void CScene::LoadTile(const wstring& _strRelativePath, bool _activate)
{
	wstring strFilePath = CPathManager::GetInstance()->GetContentPath();
	strFilePath += _strRelativePath;

	// 커널 오브젝트
	FILE* pFile = nullptr;

	// 세 번째 인자 w는 쓰기, r는 읽기, rb는 바이너리 모드로 읽겠다
	// 읽기 모드에서 해당 경로에 파일이 없을 경우에 nullptr 반환
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// 타일 가로 세로 개수, 타일 타입 불러오기
	UINT xCount = 0;
	UINT yCount = 0;
	UINT TileNumber = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&TileNumber, sizeof(UINT), 1, pFile);


	// 불러온 개수에 맞게 EmptyTile 들 만들어두기
	CreateTile(xCount, yCount, TileNumber, _activate);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = m_iLoadedTileCount; i < vecTile.size(); i++)
	{
		(((CTile*)vecTile[i])->Load(pFile));
	}
	m_iLoadedTileCount += xCount * yCount;
	fclose(pFile);
}

void CScene::SetMonster(MONSTER_TYPE _eMonsterType, int _ptx, int _pty, bool _activate, int _range /*= 0*/, bool horizen /*= false*/, bool _ismove /*false*/)
{
	switch (_eMonsterType)
	{
	case MONSTER_TYPE::SPIDER:
	{
		CSpider* pSpiderObj = new CSpider;
		pSpiderObj->SetName(L"Spider");
		pSpiderObj->SetScale(Vector2{ 100, 100 });
		pSpiderObj->m_bActive = _activate;
		pSpiderObj->SetBoardPos(POINT{ _ptx ,_pty });
		pSpiderObj->SetPos(Vector2{ (BOARD_TILE / 2) + (BOARD_TILE * _ptx), (BOARD_TILE / 2) + (BOARD_TILE * _pty) });
		AddObject(pSpiderObj, GROUP_TYPE::MONSTER);
		break;
	}
	case MONSTER_TYPE::GUARDIAN:
	{
		CGuardian* pGuradian = new CGuardian;
		pGuradian->SetName(L"Guardian");
		pGuradian->SetScale(Vector2{ 100, 100 });
		pGuradian->m_bActive = _activate;
		pGuradian->SetBoardPos(POINT{ _ptx ,_pty });
		pGuradian->SetPos(Vector2{ (BOARD_TILE / 2) + (BOARD_TILE * (_ptx)), (BOARD_TILE / 2) + (BOARD_TILE * _pty) });
		pGuradian->SetCenter(POINT{ _ptx ,_pty });
		pGuradian->SetMoveRange(_range);
		pGuradian->SetIsHorizen(horizen);
		pGuradian->SetCanMove(_ismove);
		AddObject(pGuradian, GROUP_TYPE::MONSTER);
		break;
	}
	case MONSTER_TYPE::TIMEGUARDIAN:
	{
		CTimeGuardian* pTimeGuradian = new CTimeGuardian;
		pTimeGuradian->SetName(L"Guardian");
		pTimeGuradian->SetScale(Vector2{ 100, 100 });
		pTimeGuradian->m_bActive = _activate;
		pTimeGuradian->SetPos(Vector2{ (BOARD_TILE / 2) + (BOARD_TILE * (BOARD_PENDING + _ptx)), (BOARD_TILE / 2) + (BOARD_TILE * _pty) });
		pTimeGuradian->SetBoardPos(POINT{ _ptx ,_pty });
		AddObject(pTimeGuradian, GROUP_TYPE::MONSTER_ABSOLUTE);
		break;
	}
	default:
		break;
	}
}

void CScene::SetObject(GROUP_TYPE _eObjectType, int _ptx, int _pty, int _TriggerNumber, bool _activate)
{
	switch (_eObjectType)
	{
	case GROUP_TYPE::LEVER:
	{
		CLever* pLever;

		if (_activate)
		{
			pLever = new CLever(!m_bIsPast);
		}
		else
		{
			pLever = new CLever(m_bIsPast);
		}
		pLever->SetName(L"Lever");
		pLever->SetScale(Vector2(100.f, 100.f));
		pLever->m_bActive = _activate;
		pLever->SetPos(Vector2((BOARD_TILE / 2) + (BOARD_TILE * _ptx), (BOARD_TILE / 2) + (BOARD_TILE * _pty)));
		pLever->SetTriggerNumber(_TriggerNumber);
		AddObject(pLever, GROUP_TYPE::LEVER);
	}
	break;
	case GROUP_TYPE::DOOR:
	{
		CDoor* pDoor = new CDoor;
		pDoor->SetName(L"Lever");
		pDoor->SetScale(Vector2(100.f, 100.f));
		pDoor->m_bActive = _activate;
		pDoor->SetPos(Vector2((BOARD_TILE / 2) + (BOARD_TILE * _ptx), (BOARD_TILE / 2) + (BOARD_TILE * _pty)));
		AddObject(pDoor, GROUP_TYPE::DOOR);
	}
	break;
	default:
		break;
	}
}

void CScene::SetTrap(TILE_TYPE _eTileType, int _StartCount, int _EndCount, bool TrapOn)
{

	switch (_eTileType)
	{
	case TILE_TYPE::FIRE:				// 가시
	{
		// 타일의 처음부터 끝까지 반복문 실행
		vector<CObject*>::iterator iter = m_arrObj[(UINT)GROUP_TYPE::TILE].begin();
		int StartCount = _StartCount;
		int EndCount = _EndCount;

		for (; iter != m_arrObj[(UINT)GROUP_TYPE::TILE].end(); iter++)
		{
			CTile* tile;
			tile = (CTile*)(*iter);

			// 맞는 타일 타입을 찾으면 StartCount가 0이 될때까지 차감한 다음에 TrapOn 지정


			if (tile->GetTileType() == (int)_eTileType)
			{
				if (StartCount > 0)
					StartCount--;
				else
				{
					if (EndCount <= 0)
						return;

					tile->GetThron()->SetIsOn(!TrapOn);
					EndCount--;
				}
			}
		}
	}
	break;
	case TILE_TYPE::TRIGGER:			// 불
	{
		// 타일의 처음부터 끝까지 반복문 실행
		vector<CObject*>::iterator iter = m_arrObj[(UINT)GROUP_TYPE::TILE].begin();
		int StartCount = _StartCount;
		int EndCount = _EndCount;

		for (; iter != m_arrObj[(UINT)GROUP_TYPE::TILE].end(); iter++)
		{
			CTile* tile;
			tile = (CTile*)(*iter);

			// 맞는 타일 타입을 찾으면 StartCount가 0이 될때까지 차감한 다음에 TrapOn 지정


			if (tile->GetTileType() == (int)_eTileType && tile->GetTriggerNumber() >= 5 && tile->GetTriggerNumber() < 10)
			{
				if (StartCount > 0)
					StartCount--;
				else
				{
					if (EndCount <= 0)
						return;

					tile->CreateFire(GROUP_TYPE::LEVER);
					tile->GetFire()->m_bActive = TrapOn;

					EndCount--;
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

void CScene::SetDefaultCollision()
{
	// 충돌 매트릭스 지정 ( 충돌해야할 두 객체를 체크, 체크하지 않으면 겹쳐도 충돌하지 않는다. )
	// Player에 대한 Monster, Trap, Tile 의 처리
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_ABSOLUTE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TRAP_FIRE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TRAP_ARROW);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE_APPERENCE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);
	// Player 공격에 대한 Monster 처리
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::RELICS);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER_ABSOLUTE);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::LEVER);
	// Monster와 Tile 의 충돌처리
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::TILE, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInstance()->CheckGroup(GROUP_TYPE::TILE, GROUP_TYPE::MONSTER_ABSOLUTE);

}

void CScene::SetUI(bool _isPast)
{
	Vector2 vResoulution = Vector2(1920, 1080);

	Vector2 Stone = Vector2(300.f, 200.f);

	CUI* pStone_Cur = new CStone(_isPast);
	pStone_Cur->SetName(L"Stone_Cur");
	pStone_Cur->SetScale(Stone);
	pStone_Cur->SetPos(Vector2((vResoulution.x / 2) - (pStone_Cur->GetScale().x / 2 + 10.0f), 20.f));
	pStone_Cur->m_bActive = !_isPast;
	AddObject(pStone_Cur, GROUP_TYPE::Event_UI);

	CUI* pStone_Past = new CStone(!_isPast);
	pStone_Past->SetName(L"Stone_Past");
	pStone_Past->SetScale(Stone);
	pStone_Past->SetPos(Vector2((vResoulution.x / 2) - (pStone_Past->GetScale().x / 2 + 10.0f), 20.f));
	pStone_Past->m_bActive = _isPast;
	AddObject(pStone_Past, GROUP_TYPE::Event_UI);


	CUI* pPreferences = new CPreferences;
	pPreferences->SetName(L"Preferences");
	pPreferences->SetScale(Vector2(100.f, 100.f));
	pPreferences->SetPos(Vector2(20.f, 20.f));
	AddObject(pPreferences, GROUP_TYPE::UI);

	// 시계 및 포이즌 카운터 

	// 독 및 시계 크기조절
	Vector2 CountUI = Vector2(200.f, 200.f);

	// 시계를 카운팅 하기위한 공간
	CUI* pClockCount = new CClockConut;
	pClockCount->SetName(L"ClockCount");
	pClockCount->SetScale(CountUI);
	pClockCount->SetPos(Vector2(vResoulution.x - (pClockCount->GetScale().x + 50.f), vResoulution.y - 250.f));
	AddObject(pClockCount, GROUP_TYPE::UI);

	// 시계이미지를 넣기 위한 공간
	CUI* pClock = new CClock;
	pClock->SetName(L"Clock");
	pClock->SetScale(CountUI);
	pClock->SetPos(Vector2(vResoulution.x - (pClock->GetScale().x + 300.f), vResoulution.y - 250.f));
	AddObject(pClock, GROUP_TYPE::UI);

	// 독을 카운팅 하기위한 공간
	CUI* pPoisonCount = new CPoisonCount;
	pPoisonCount->SetName(L"PoisonCount");
	pPoisonCount->SetScale(CountUI);
	pPoisonCount->SetPos(Vector2(vResoulution.x - (pClockCount->GetScale().x + +50.f), 50.f));
	AddObject(pPoisonCount, GROUP_TYPE::UI);

	// 독 이미지를 넣기 위한 공간
	CUI* pPoison = new CPoison;
	pPoison->SetName(L"Posion");
	pPoison->SetScale(CountUI);
	pPoison->SetPos(Vector2(vResoulution.x - (pPoison->GetScale().x + 300.f), 50.f));
	AddObject(pPoison, GROUP_TYPE::UI);
}
