// WindowsProject2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "WindowsProject2.h"
#include "CGameProcess.h"
#include "CKeyManager.h"
#include "SoundManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
// wchar_t 타입 변수 배열 100개
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
// wchar_t 타입 변수 배열 100개
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
// ATOM = unsigned short
ATOM                MyRegisterClass(HINSTANCE hInstance);
// BOOL = int
BOOL                InitInstance(HINSTANCE, int);
// LRESULT = __int64 
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// INT_PTR = long long
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 메인 함수 ( SAL )
// 실행 된 프로세스의 시작 주소
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 메모리 릭(누수) 체크
    // https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(506);

    // 참조 되지 않는 변수 입니다
    // 이 코드는 아무 의미도 없다. UNPEFERENCED_PARAMERTER (변수) = 변수
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    CGameProcess* _pGameProcess = new CGameProcess;
    
    if (FAILED(_pGameProcess->Initialize(g_hWnd, POINT{ 16 * 120, 9 * 120 })))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

        return FALSE;
    }
    
    // 단축키
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    // 메세지 구조체
    MSG msg;

    // GetMessage : 메세지를 받으면 메세지 큐로 그 메세지를 가져오겠다
    // msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료
    
    // PeekMessage : 메세지 유무와 관계없이 반환
    // 메세지가 있으면 true, 메세지가 없으면 false
    // 메세지큐에서 메세지를 확인한 경우 true, 메세지큐에 메세지가 없는 경우 false를 반환한다

    while (true)
	{
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        // 메세지가 발생하지 않는 대부분의 시간
        else
        {
            _pGameProcess->Progress();
        }
    }

    SoundManager::GetInstance()->FinalRlease();

    delete _pGameProcess;

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // struct 구조체
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // 프로시저
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    // 해당 키 값에 데이터 정보를 세팅한다
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우의 정보를 szWindowClass의 키값으로 찾는다
   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   SetMenu(g_hWnd, NULL);
   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

// 윈도우 프로시저 함수 선언 ( 추가 : 이건재 )
INT_PTR __stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static bool isFullScreen = false;
    static RECT windowRect;
    static bool isMinimized = false; // 최소화 상태 여부를 저장하는 변수
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
                // 메뉴 타일 개수 선택시 TILE_COUNT창 생성 ( 추가 : 이건재 )
            case ID_MENU_TILE:                                                  
            {
                INT_PTR iRet = DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);
            }
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  // 무효화 영역(Invalidate)이 발생한 경우
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        CKeyManager::GetInstance()->SetMousePos((float)LOWORD(lParam), (float)HIWORD(lParam));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_ACTIVATE:
	{
		// 포커스 상태 변경을 감지하여 전체화면 모드를 전환하거나 해제
		if (LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)
		{
			if (!isFullScreen)
			{
				// 전체화면 모드로 전환
				DEVMODE dmSettings;
				memset(&dmSettings, 0, sizeof(dmSettings));
				dmSettings.dmSize = sizeof(dmSettings);
				dmSettings.dmPelsWidth = 1920; // 전체화면 해상도 설정
				dmSettings.dmPelsHeight = 1080;
				dmSettings.dmBitsPerPel = 32;
				dmSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if (ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
				{
					if (isMinimized)
					{
						// 최소화 상태이면 윈도우 복원
						ShowWindow(hWnd, SW_RESTORE);
						isMinimized = false;
					}

					// 이전 윈도우 위치 및 크기 저장
					GetWindowRect(hWnd, &windowRect);

					SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE); // 윈도우 스타일 변경
					SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW); // 윈도우 위치 및 크기 변경
					isFullScreen = true;
				}
			}
		}
		else
		{
			if (isFullScreen)
			{
				// 전체화면 모드 해제
				ChangeDisplaySettings(NULL, 0); // 이전 디스플레이 설정으로 복원
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE); // 윈도우 스타일 복원

				if (isMinimized)
				{
					// 최소화 상태로 윈도우 유지
					ShowWindow(hWnd, SW_MINIMIZE);
				}
				else
				{
					// 이전 윈도우 위치 및 크기로 복원
					SetWindowPos(hWnd, NULL, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);
				}
                // ShowWindow(hWnd, SW_MINIMIZE);
				isFullScreen = false;
			}
		}
	}
	break;
    default:
        // 기본 프로시저
        // 키 입력 관련되서는 아무것도 안해준다
        // 내가 직접 관리하지 않는 모든 메세지는 여기서 처리해준다
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
