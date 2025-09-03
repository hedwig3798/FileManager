#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyManager.h"
#include "CTile.h"
#include "CGameProcess.h"

//#include "CResMgr.h"
#include "TextureManager.h"

#include "CSceneManager.h"
#include "CPathManager.h"
#include "SoundManager.h"

#include "resource.h"
// 일시정지 패널 UI
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CContinue.h"
#include "CReStart.h"
#include "CMainMenu.h"
// 인게임 안에서 UI
#include "CMiniMap.h"
#include "CStone.h"
#include "CPreferences.h"
#include "CPoison.h"
#include "CClock.h"
#include "CClockConut.h"
#include "CPoisonCount.h"
// CScene_Tool 클래스 생성 ( 추가 : 이건재 )
CScene_Tool::CScene_Tool(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)
{
	m_hScreenDC = hDC;
	m_hWnd = hWnd;
	m_ScreenRes = screenRes;
}

CScene_Tool::~CScene_Tool()
{

}
bool CScene_Tool::Exit()
{
	SoundManager::GetInstance()->Stop(BGM);
	return false;
}

// 툴 에디터 업데이트 ( 추가 : 이건재 )
void CScene_Tool::Update()
{
	// 부모쪽 update()함수를 호출
	CScene::Update();

	SetTileIdx();

// 	if (CKeyManager::GetInstance()->GetKeyState(KEY::ENTER) == KEY_STATE::TAP)
// 	{
// 		// 이벤트 등록 ( 추가 : 이건재 )
// 		ChangeScene(SCENE_TYPE::START);
// 	}
	if (CKeyManager::GetInstance()->GetKeyState(KEY::LSHIFT) == KEY_STATE::TAP)
	{
		// 타일 저장하기 ( 추가 : 이건재 )
		SaveTileData();
	}
	if (CKeyManager::GetInstance()->GetKeyState(KEY::CTRL) == KEY_STATE::TAP)
	{
		// 타일 불러오기 ( 추가 : 이건재 )
		LoadTileDate();
	}
}

void CScene_Tool::Enter(bool _isPast)
{
	// 타일 생성
	CreateTile(13, 9, 2, true);

}
 
// 마우스 위치에 따라 타일 값 세팅하기 ( 추가 : 이건재 )
void CScene_Tool::SetTileIdx()
{
	static int CopyNumber = 0;

	// 마우스 좌표를 찾아 타일 크기만큼 나눠서 타일 배열 위치 찾기
	Vector2 vMousePos = CKeyManager::GetInstance()->GetMousePos();

	int iTileX = (int)GetTileX();
	int iTileY = (int)GetTileY();

	int iCol = (int)vMousePos.x / BOARD_TILE;
	int iRow = (int)vMousePos.y / BOARD_TILE;

	// 마우스 좌표가 타일 좌표 위치 벗어났으면 예외처리
	if (vMousePos.x < 0.f || iTileX <= iCol
		|| vMousePos.y < 0.f || iTileY <= iRow)
	{
		return;
	}

	UINT iIdx = iRow * iTileX + iCol;

	// 좌클릭 했을 때 마우스 좌표 찾아서 타일 인덱스 더하기 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::LBTN) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
	
	// 우클릭 했을 때 마우스 좌표 찾아서 타일 인덱스 빼기 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::RBTN) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->MinusImgIdx();
	}

	// 마우스 위치에 있는 타일 위에서 C를 눌렀을 때, 해당 타일 콜라이더 생성 및 삭제 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::L) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->CheckCollider();
	}

	// 마우스 위치에 있는 타일 위에서 R를 눌렀을 때, 해당 타일 타일 인덱스 번호 복사 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::R) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		CopyNumber = ((CTile*)vecTile[iIdx])->GetImgIdx();
	}

	// 마우스 위치에 있는 타일 위에서 T를 눌렀을 때, 해당 타일 인덱스 번호 붙여넣기 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::T) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->SetImgIdx(CopyNumber);
	}

	// 마우스 위치에 있는 타일 위에서 H를 눌렀을 때, 해당 타일 타입 더하기 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::H) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddTileType();
	}

	// 마우스 위치에 있는 타일 위에서 N를 눌렀을 때, 해당 타일 트리거 넘버 더하기 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::N) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddTriggerNumber();
	}

	// 마우스 위치에 있는 타일 위에서 M를 눌렀을 때, 해당 타일 트리거 넘버 더하기 ( 추가 : 이건재 )
	if (CKeyManager::GetInstance()->GetKeyState(KEY::M) == KEY_STATE::TAP)
	{
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddTriggerDir();
	}
}

// 윈도우에서 제공해주는 함수를 통해 구조체 저장하고 파일 저장하기 ( 추가 : 이건재 )
void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";				// ALL\0*. 은 ALL에 대항하는 아무 이름이 와도 되고 아무 확장자여도 된다
	ofn.nFileExtension = 0;
	ofn.lpstrFileTitle = nullptr;								// 수정 가능한 타이틀 제목
	ofn.nMaxFileTitle = 0;

	wstring strTIleFolder = CPathManager::GetInstance()->GetContentPath();
	strTIleFolder += L"tile";
	
	ofn.lpstrInitialDir = strTIleFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// Modal
	// 파일을 저장할 때 절대 경로의 주소가 szName의 문자 배열에 담긴다
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

// 윈도우에서 제공해주는 함수를 통해 구조체 저장하고 파일 불러오기 ( 추가 : 이건재 )
void CScene_Tool::LoadTileDate()
{
	wchar_t szName[256] = {};

	// 이 구조체는 윈도우에서 제공해주는 구조체로
	// 윈도우에서 파일 불러오기 저장하는 윈도우 함수에 전달되는 구조체이다
	// https://learn.microsoft.com/ko-kr/windows/win32/api/commdlg/ns-commdlg-openfilenamea?redirectedfrom=MSDN&devlangs=cpp&f1url=%3FappId%3DDev16IDEF1%26l%3DKO-KR%26k%3Dk(COMMDLG%252FOPENFILENAME)%3Bk(OPENFILENAME)%3Bk(DevLang-C%252B%252B)%3Bk(TargetOS-Windows)%26rd%3Dtrue
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";				// ALL\0*. 은 ALL에 대항하는 아무 이름이 와도 되고 아무 확장자여도 된다
	ofn.nFileExtension = 0;
	ofn.lpstrFileTitle = nullptr;								// 수정 가능한 타이틀 제목
	ofn.nMaxFileTitle = 0;

	wstring strTIleFolder = CPathManager::GetInstance()->GetContentPath();
	strTIleFolder += L"tile";

	ofn.lpstrInitialDir = strTIleFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	// 파일을 저장할 때 전체 경로의 주소가 szName의 문자 배열에 담긴다
	if (GetOpenFileName(&ofn))
	{
		wstring strFilePath = szName;
		
		// 상대 경로 = 전체 경로 - 절대 경로
		size_t iAbsLen = wcslen(CPathManager::GetInstance()->GetContentPath());
		size_t iFullLen = strFilePath.length();
		
		wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);

		LoadTile(strRelativePath, true);
	}
}

// 툴 씬 타일 변환하고 저장하기 ( 추가 : 이건재 )
void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// 커널 오브젝트
	FILE* pFile = nullptr;

	// 세 번째 인자 w는 쓰기, r는 읽기, rb, wb는 이진수 데이터로 읽겠다
	// 아스키 코드 중에 ESC = 27로 만약에 r로 읽다가 27을 읽으면 그대로 탈출하는 현상이 발생할 수도 있기 떄문에 rb, wb를 쓴다
	// 쓰기 모드라면 파일이 없어도 쓰는 모드이기 때문에 파일이 생성된다
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	assert(pFile);

	// 데이터 저장
	// 타일 가로세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();
	UINT TileTypeNumber = GetTileTypeNumber();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&TileTypeNumber, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}






// Tile Count 윈도우 창 프로시저 ( 추가 : 이건재 )
// ======================
// Tile Count Window Proc
// ======================
INT_PTR __stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// GetDlgItemInt는 텍스트 박스 안에 있는 문자열 데이터를 int형으로 바꿔서 반환해준 것이다
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			UINT TileFileNumber = GetDlgItemInt(hDlg, IDC_EDIT3, nullptr, false);

			CScene* pCurScene = CSceneManager::GetInstance()->GetCurScene();

			// ToolScene 확인
			// pCurScene이 TooScene이면 ToolScene 반환, 아니면 nullptr 반환
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount, TileFileNumber, true);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}