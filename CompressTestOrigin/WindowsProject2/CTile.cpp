#include "pch.h"
#include "CTile.h"

#include "Texture.h"
#include "CCollider.h"
#include "SelectGDI.h"
#include "CScene.h"
#include "CGameProcess.h"
#include "CMissile.h"
#include "CFire.h"
#include "CPoisonTile.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CFootButton.h"

CTile::CTile(HDC hDC)
	: m_hDC(hDC)
	, m_pTileTex(nullptr)
	, m_iImgIdx(0)
	, m_CheckCollider(true)
	, m_TileType(0)
	, m_TriggerNumber(0)
	, m_TriggerDir(0)
	, m_iOldImgIdx(0)
	, pFire(nullptr)
	, pThron(nullptr)
	, pPoison(nullptr)
	, m_TriggerOnce(true)
{
	CreateCollider();
	// CreateBrushPen();
	SetScale(Vector2(BOARD_TILE, BOARD_TILE));
}

CTile::~CTile()
{
	// 펜 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}


// Tool Scene에서 타일의 콜라이더를 세팅하는 함수 ( 추가 : 이건재 )
void CTile::CheckCollider()
{
	if (m_CheckCollider)
	{
		GetCollider()->SetOffsetPos(Vector2(BOARD_TILE / 2, BOARD_TILE / 2));
		GetCollider()->SetScale(Vector2(BOARD_TILE / 4, BOARD_TILE / 4));
		m_CheckCollider = false;
		if (m_TileType == (int)TILE_TYPE::TRAP)
		{
			CFootButton* fb = new CFootButton(CSceneManager::GetInstance()->GetCurScene()->m_bIsPast);
			fb->SetName(L"Deco obj");
			fb->SetPos(GetPos());
			fb->SetScale(GetScale());
			fb->m_bActive = m_bActive;
			CreateObject(fb, GROUP_TYPE::TILE_APPERENCE);
		}
		// 타일 트리거 넘버가 15가 넘어가면 가시 타일로 바뀌게 세팅 ( 추가 : 이건재 )
		if (m_TriggerNumber >= 15 && m_TileType == (int)TILE_TYPE::TRIGGER)
		{
			m_TileType = (int)TILE_TYPE::FIRE;
		}

		if (m_TileType == (int)TILE_TYPE::WALL)
		{
			m_CheckCollider = false;
			GetCollider()->SetOffsetPos(Vector2(BOARD_TILE / 2, BOARD_TILE / 2));
			GetCollider()->SetScale(Vector2(BOARD_TILE, BOARD_TILE));
		}
		else if (m_TileType == (int)TILE_TYPE::FIRE)
		{
			pThron = new CThron(m_bActive);
			pThron->SetPos(GetPos());
			pThron->SetScale(GetScale());
			pThron->m_bActive = m_bActive;
			pThron->m_bIsPast = CSceneManager::GetInstance()->GetCurScene()->m_bIsPast;
			CreateObject(pThron, GROUP_TYPE::TILE_APPERENCE);
		}
		else if (m_TileType == (int)TILE_TYPE::POSION)
		{
			pPoison = new CPoisonTile;
			pPoison->SetPos(GetPos());
			pPoison->SetScale(GetScale());
			pPoison->m_bActive = m_bActive;
			pPoison->m_bIsPast = CSceneManager::GetInstance()->GetCurScene()->m_bIsPast;
			CreateObject(pPoison, GROUP_TYPE::TILE_APPERENCE);
		}
		else if (m_TriggerNumber >= 10 && m_TileType == (int)TILE_TYPE::TRIGGER)
		{
			m_TileType = (int)TILE_TYPE::TRIGGER_MOVABLE;
		}
	}
	else
	{
		m_CheckCollider = true;
		GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));
		GetCollider()->SetScale(Vector2(0.f, 0.f));
	}



}

void CTile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* OtherObj = _pOther->GetObj();

	if (OtherObj->GetName() == L"Player" && m_TileType == (int)TILE_TYPE::TRAP)
	{
		CSceneManager::GetInstance()->GetCurScene()->TriggerEvent(m_TriggerNumber, GROUP_TYPE::TILE);
	}
	if (OtherObj->GetName() == L"Player" && m_TileType == (int)TILE_TYPE::FATAL)
	{
		m_iImgIdx = 34;
	}
}

void CTile::Update()
{
	if (pThron != nullptr)
		pThron->m_bIsPast = CSceneManager::GetInstance()->GetCurScene()->m_bIsPast;
}

// 텍스쳐 파일의 전체 가로 길이와 세로 길이를 계산하여 BOARD_TILE로 나누어 인덱스 계산 ( 추가 : 이건재 )
void CTile::Render(HDC _dc)
{
	if (m_pTileTex == nullptr || m_iImgIdx == -1)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / BOARD_TILE;
	UINT iMaxRow = iHeight / BOARD_TILE;

	UINT iCurRow = m_iImgIdx / iMaxCol;
	UINT iCurCol = m_iImgIdx % iMaxCol;

	// 이미지 범위를 벗어난 인덱스
	if (iMaxRow <= iCurRow)
		m_iImgIdx = 0;

	Vector2 vRenderPos = GetPos();
	Vector2 vScale = GetScale();

	BitBlt(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * BOARD_TILE
		, iCurRow * BOARD_TILE
		, SRCCOPY);

	// 에디터 모드일때만 그려주기
	if (CSceneManager::GetInstance()->GetCurScene()->GetName() == L"Tool Scene")
	{
		EditMode(_dc, vRenderPos, vScale);
	}

	int a = 0;

	// 콜라이더 그려주기
	//ComponentRender(_dc);
}

// 에디터 모드일 때, 레벨 디자인 하는 사람이 보기 쉽게 색과 선으로 표시 ( 추가 : 이건재 )
void CTile::EditMode(HDC _dc, Vector2 _RenderPos, Vector2 _Scale)
{
	wstring TriggerNum = std::to_wstring(m_TriggerNumber);

	PEN_TYPE pen = PEN_TYPE::BLACK;

	// 타일 타입에 따라 색상 변경 및 함정과 트리거는 번호 표시
	if (m_TileType == (int)TILE_TYPE::MOVABLE)
		pen = PEN_TYPE::BLACK;
	else if (m_TileType == (int)TILE_TYPE::WALL)
		pen = PEN_TYPE::WHITE;
	else if (m_TileType == (int)TILE_TYPE::FATAL)
		pen = PEN_TYPE::BLUE;
	else if (m_TileType == (int)TILE_TYPE::TRAP)
	{
		pen = PEN_TYPE::PUPLE;
		TextOut(m_hDC, (int)_RenderPos.x, (int)_RenderPos.y, TriggerNum.c_str(), (int)TriggerNum.size());
	}
	else if (m_TileType == (int)TILE_TYPE::POSION)
		pen = PEN_TYPE::GREEN;
	else if (m_TileType == (int)TILE_TYPE::FIRE)
		pen = PEN_TYPE::RED;
	else if (m_TileType == (int)TILE_TYPE::TRIGGER)
	{
		pen = PEN_TYPE::ORENGE;
		TextOut(m_hDC, (int)_RenderPos.x, (int)_RenderPos.y, TriggerNum.c_str(), (int)TriggerNum.size());

		if (m_TriggerDir == (int)OBJECT_DIR::UP)
			TextOut(m_hDC, (int)_RenderPos.x + 50, (int)_RenderPos.y + 50, L"위", 1);
		else if (m_TriggerDir == (int)OBJECT_DIR::LEFT)
			TextOut(m_hDC, (int)_RenderPos.x + 50, (int)_RenderPos.y + 50, L"왼쪽", 2);
		else if (m_TriggerDir == (int)OBJECT_DIR::DOWN)
			TextOut(m_hDC, (int)_RenderPos.x + 50, (int)_RenderPos.y + 50, L"아래", 2);
		else if (m_TriggerDir == (int)OBJECT_DIR::RIGHT)
			TextOut(m_hDC, (int)_RenderPos.x + 50, (int)_RenderPos.y + 50, L"오른쪽", 3);
	}
	else if (m_TileType == (int)TILE_TYPE::SCENE_CHANGE)
		pen = PEN_TYPE::YELLOW;

	HPEN defaultPen = (HPEN)SelectObject(_dc, m_arrPen[(UINT)pen]);

	// 대각선 그리기
	MoveToEx(_dc, (int)_RenderPos.x, (int)_RenderPos.y, nullptr);
	LineTo(_dc, (int)(_RenderPos.x + _Scale.x), (int)(_RenderPos.y + _Scale.y));
	SelectObject(_dc, defaultPen);

}

void CTile::CreateFire(GROUP_TYPE _ObjectType)
{
	Vector2 vFirePos = GetPos();
	Vector2 vFireScale = Vector2((float)BOARD_TILE, (float)BOARD_TILE);

	switch ((OBJECT_DIR)m_TriggerDir)
	{
	case OBJECT_DIR::DOWN:
		vFirePos.x += BOARD_TILE / 2;
		vFirePos.y += BOARD_TILE / 2 + 60.f;
		vFireScale.x = BOARD_TILE / 2;
		vFireScale.y = BOARD_TILE * 2;
		break;
	case OBJECT_DIR::UP:
		vFirePos.x += BOARD_TILE / 2;
		vFirePos.y += BOARD_TILE / 2 - 60.f;
		vFireScale.x = BOARD_TILE / 2;
		vFireScale.y = BOARD_TILE * 2;
		break;
	case OBJECT_DIR::RIGHT:
		vFirePos.x += BOARD_TILE / 2 + 60.f;
		vFirePos.y += BOARD_TILE / 2;
		vFireScale.x = BOARD_TILE * 2;
		vFireScale.y = BOARD_TILE / 2;
		break;
	case OBJECT_DIR::LEFT:
		vFirePos.x += BOARD_TILE / 2 - 60.f;
		vFirePos.y += BOARD_TILE / 2;
		vFireScale.x = BOARD_TILE * 2;
		vFireScale.y = BOARD_TILE / 2;
		break;
	default:
		break;
	}

	if (pFire == nullptr)
	{
		//CreateObject()
		pFire = new CFire((OBJECT_DIR)m_TriggerDir);					// 추가 
		pFire->SetName(L"Fire_Trap");
		pFire->SetPos(vFirePos);
		pFire->m_bActive = !(CSceneManager::GetInstance()->GetCurScene()->m_bIsPast);
		pFire->SetScale(Vector2(vFireScale));
		CreateObject(pFire, GROUP_TYPE::TRAP_FIRE);
	}
	else if (_ObjectType == GROUP_TYPE::LEVER && pFire != nullptr)
	{
		if (pFire->TriggerOn)
			pFire->TriggerOn = false;
		else
			pFire->TriggerOn = true;
	}
}

// 함정 발생 ( 이벤트에서 발생해서 이 함수 실행 )
void CTile::TriggerOn(int _TriggerNumber, GROUP_TYPE _ObjectType)
{
	if (m_TriggerNumber == _TriggerNumber && m_TileType == (UINT)TILE_TYPE::TRIGGER)
	{
		if (m_TriggerNumber < 5 && m_TriggerOnce)
		{
			m_TriggerOnce = false;

			//CreateObject()
			Vector2 vMissilePos = GetPos();
			vMissilePos.x += 60.f;
			vMissilePos.y += 60.f;
			CMissile* pMissile = new CMissile;
			pMissile->SetName(L"Missile_Trap");
			pMissile->SetPos(vMissilePos);
			pMissile->SetScale(Vector2(25.f, 25.f));
			pMissile->SetDir((OBJECT_DIR)m_TriggerDir);
			CreateObject(pMissile, GROUP_TYPE::TRAP_ARROW);
		}
		if (m_TriggerNumber >= 5 && m_TriggerNumber < 10)
		{
			CreateFire(_ObjectType);
		}
	}
	if (m_TriggerNumber == _TriggerNumber && (m_TileType == (UINT)TILE_TYPE::TRIGGER_MOVABLE || m_TileType == (UINT)TILE_TYPE::TRIGGER_FATAL)) {
		if (m_TriggerNumber >= 10 && m_TriggerNumber < 15 && m_TriggerOnce)
		{
			m_TriggerOnce = false;

			if (m_TileType == (UINT)TILE_TYPE::TRIGGER_MOVABLE)
			{
				m_TileType = (UINT)TILE_TYPE::TRIGGER_FATAL;
				m_iOldImgIdx = m_iImgIdx;
				m_iImgIdx = 34;
			}
			else
			{
				m_TileType = (UINT)TILE_TYPE::TRIGGER_MOVABLE;
				m_iImgIdx = m_iOldImgIdx;
			}
		}
	}
	// 가시 타일 트리거, 발판 밟으면 무조건 가시가 올라오게 설정 ( 추가 : 이건재 )
	if (m_TriggerNumber == _TriggerNumber && m_TileType == (UINT)TILE_TYPE::FIRE)
	{
		if (m_TriggerNumber >= 15 && _ObjectType == GROUP_TYPE::TILE && m_TriggerOnce)
		{
			m_TriggerOnce = false;
			pThron->SetIsOn(!pThron->GetIsOn());
		}

		if (m_TriggerNumber >= 15 && _ObjectType == GROUP_TYPE::LEVER)
		{
			pThron->SetIsOn(!pThron->GetIsOn());
		}
	}
}




// 타일 상태 (텍스쳐 인덱스, 콜리전 상태) 저장하기 ( 추가 : 이건재 )
void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
	fwrite(&m_CheckCollider, sizeof(bool), 1, _pFile);
	fwrite(&m_TileType, sizeof(int), 1, _pFile);
	fwrite(&m_TriggerNumber, sizeof(int), 1, _pFile);
	fwrite(&m_TriggerDir, sizeof(int), 1, _pFile);
}

// 타일 상태 (텍스쳐 인덱스, 콜리전 상태) 불러오기 ( 추가 : 이건재 )
void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
	fread(&m_CheckCollider, sizeof(bool), 1, _pFile);
	fread(&m_TileType, sizeof(int), 1, _pFile);
	fread(&m_TriggerNumber, sizeof(int), 1, _pFile);
	fread(&m_TriggerDir, sizeof(int), 1, _pFile);
	SetName(L"Tile");
	m_iOldImgIdx = m_iImgIdx;
	if (m_CheckCollider)
		m_CheckCollider = false;
	else
		m_CheckCollider = true;

	CheckCollider();
}

void CTile::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));

	// red Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::PUPLE] = CreatePen(PS_SOLID, 2, RGB(148, 0, 211));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	m_arrPen[(UINT)PEN_TYPE::ORENGE] = CreatePen(PS_SOLID, 2, RGB(255, 165, 0));
}
