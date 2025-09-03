#include "pch.h"

#include "CPathManager.h"


CPathManager::CPathManager()
	: m_szContentPath{}
{

}

CPathManager::~CPathManager()
{

}

void CPathManager::Initialize()
{
	// 절대 경로 : D:\GA5th1Q_Project\TimeTravel\5_Project\window-api-study\Output\bin		// release
	// 절대 경로 : D:\GA5th1Q_Project\TimeTravel\5_Project\window-api-study\Output\bin_debug	// debug
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	// 상위 폴더로
	// Debug로 실행할 경우에는 \\Output\\bin.Debug로 저장되니
	// \\Output 으로 설정하기 위해
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// 경로 : D:\GA5th1Q_Project\TimeTravel\5_Project\window-api-study\Output\

	// \\Output\\bin\\content로 문자열 입력
	// 나머지 리소스 texture와 sound로 구분되어 있는데 이는 각 오브젝트에서 설정한다
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}