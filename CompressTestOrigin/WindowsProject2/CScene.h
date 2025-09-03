#pragma once
#include "CCollisionManager.h"
#include "CPlayer.h"
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
// 전방선언
class CObject;

/// <summary>
/// Scene들의 모든 부모가 되는 최상위 클래스
/// IScene이 좋은 이름일텐데..
/// 
/// 2023.05.22
/// </summary>

enum class MONSTER_TYPE
{
	SPIDER,
	GUARDIAN,
	TIMEGUARDIAN
};

class CScene
{
public:
	///컷신과 엔딩은 Scene클래스의 상속을 받았기 때문에, 같은 함수 상속받아서 쓰려면 인자의 종류, 개수 같이 써야함
	CScene(HWND hWnd, HDC hDC, POINT screenRes);
	virtual ~CScene();
	SCENE_TYPE m_eNextScene;
	SCENE_TYPE m_eNowScene;
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }
	UINT GetTileTypeNumber() { return m_iTileTypeNumber; }

public:
	virtual void Update();
	virtual void Finalupdate();
	virtual void Render(HDC _dc);
	void TriggerEvent(int _TileTriggerNumber, GROUP_TYPE _ObjectType);
	void DeveloperMode(int ModeType);

public:
	// 값이 기입된 가상 함수는 자식 클래스에서 구현해야될 함수인 것을 알리는 용도이다
	virtual void Enter(bool _isPast) = 0;		// 해당 Scene에 진입 시 호출
	virtual bool Exit() = 0;		// 해당 Scene을 탈출 시 호출

public:
	// 구현부를 헤더에 만들면 해당 함수는 인라인 처리되어 함수 호출 스택이 생기지 않아 성능에 차이가 많이 없다.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); };

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	int m_iLoadedTileCount;

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _iYCount, UINT _TileFileNumber, bool _activate);
	void LoadTile(const wstring& _strRelativePath, bool _activate);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }// 05월 21일 이현장 추가

	void SetMonster(MONSTER_TYPE _eMonsterType, int _ptx, int _pty, bool activate, int _range = 0, bool horizen = false, bool _ismove = true);
	void SetObject(GROUP_TYPE _eObjectType, int _ptx, int _pty, int _TriggerNumber, bool _activate);
	void SetTrap(TILE_TYPE _eTileType, int _StartCount, int _EndCount, bool TrapOn);

	void SetDefaultCollision();

	void SetUI(bool _isPast);

public:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// 오브젝트를 저장 및 관리할 벡터를 그룹 갯수만큼 선언
	HWND m_hWnd;
	HDC m_hDC;
	POINT m_screenRes;
	bool m_bIsPast;
	bool CollisionVisible;

private:
	wstring				m_strName;			// Scene 이름

	UINT				m_iTileX;			// 타일 가로 개수
	UINT				m_iTileY;			// 타일 세로 개수
	UINT				m_iTileTypeNumber;	// 타일 타입

};