#include "pch.h"
#include "CGameProcess.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyManager.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventMgr.h"
#include "CUIMgr.h"
#include "SoundManager.h"
//#include "CResMgr.h"
#include "TextureManager.h"

CGameProcess::CGameProcess()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CGameProcess::~CGameProcess()
{
	// DC 반환
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	// 펜 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CGameProcess::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255,0,0));

	// red Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::PUPLE] = CreatePen(PS_SOLID, 2, RGB(148, 0, 211));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	m_arrPen[(UINT)PEN_TYPE::ORENGE] = CreatePen(PS_SOLID, 2, RGB(255, 165, 0));
}


// init 순서
// 1. 윈도우 핸들과 윈도우 크기를 세팅할 x, y좌표를 담은 POINT를 매개변수로 받아와서 세팅한다. 
// ( 이때 CCore와 Mgr 클래스들은 이미 싱글톤 패턴에서 static으로 생성했기 때문에,
//  데이터 영역에 메모리가 잡혀 있는 상태여서 객체를 생성할 필요가 없고 범위 지정 연산자 ::GetInstance()로 해당 객체의 주소를 가져올 수 있다. )
// 2. 해상도에 맞게 윈도우 크기 조정
// 3. 이중 버퍼링 용도의 비트맵과 DC를 만든다
// 4. 비트맵을 SelectObject로 선택한다
// 5. Manager 초기화
// 5-1. CPathMgr : 리소스 파일을 가져올 경로를 wstring으로 저장
// 5-2. CTimeMgr : 시간 세팅
// 5-3. CKeyMgr : 입력 키 세팅
// 5-4. CSceneMgr : 생성할 맵을 만들고 현재 맵 선택
// 5-5 CCollisionMgr : 현재로서는 없음
int CGameProcess::Initialize(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

// 	// 해상도에 맞게 윈도우 크기 조정
 	//RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
 	//AdjustWindowRect(&rt, WS_BORDER , true);										// 윈도우 창 생성
 	//SetWindowPos(m_hWnd, nullptr,100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);		//

	// 우리 윈도우 창의 hdc를 가져오고
	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);													// m_hDC와 호환되는 DC 생성

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);								// m_memDC에 m_hBit가 오브젝트로 선택 되었다
	DeleteObject(hOldBit);

	// 자주 사용 할 펜 및 브러쉬 생성
	// CreateBrushPen();

	// 
	SoundManager::GetInstance()->Init();
	SoundManager::GetInstance()->Loading();
	// Manager 초기화
	CPathManager::GetInstance()->Initialize();
	CTimeManager::GetInstance()->Initialize();
	CKeyManager::GetInstance()->Initialize();
	//CResMgr::GetInstance()->m_hDC = m_hDC;
	TextureManager::GetInstance()->m_hDC = m_hDC;
	// 맵을 추가할 경우 
	// CSceneMgr의 Init함수에 맵 추가!
	// define.h에서 SCENE_TYPE 추가!
	// CSene 클래스의 자식 클래스를 생성 후에 Enter()함수에서 맵에 배치할 오브젝트 생성!
	// 
	// 오브젝트를 추가할 경우
	// 만약에 오브젝트를 새로 만들 경우에 CObject클래스의 자식 클래스를 생성하고
	// define.h에서 GROUP_TYPE 추가!
	// 오브젝트 생성자에서 컴포넌트인 Collider와 Animation을 붙여줄 수 있습니다
	// 만약 Collider를 추가할 경우에 OnCollision함수(3개)들을 사용할 수 있습니다
	CSceneManager::GetInstance()->Initialize(m_hWnd, m_memDC, m_ptResolution);
	CCollisionManager::GetInstance()->Initialize();

	return S_OK;
}


// update 순서
// 1. TimeMgr, KeyMgr
// 2. Scene update -> CurScene(현재 맵)의 Object*->update
// 3. Scene fianlupdate -> CurScene(현재 맵)의 Object*->finalupdate 실행
// 4. Collision -> 콜리전 충돌 체크 후 -> (충돌했을 경우) Object*->OnCollision 함수 실행
// 
// render 순서
// 5. 화면 클리어
// 6. Scene render -> CurScene(현재 맵)의 Object*->render 실행
// 7. BitBlt으로 현재 윈도우 인스턴스의 HDC로 그려준다
// 
// Event
// 8. EventMgr update -> Object들을 생성하거나, 삭제하거나, CurScene(현재 맵)을 변경할 경우
void CGameProcess::Progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeManager::GetInstance()->Update();
	CKeyManager::GetInstance()->Update();

	// =============
	// SCene Update
	// =============
	CSceneManager::GetInstance()->Update();

	// 충돌체크
	CCollisionManager::GetInstance()->Update();

	// UI 이벤트 체크
	CUIMgr::GetInstance()->Update();

	// =========
	// Rendering
	// =========
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneManager::GetInstance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	// =============
	// 이벤트 지연처리
	// =============
	CEventMgr::GetInstance()->Update();

}