#pragma once

#include <windows.h>

/// <summary>
/// 길찾기를 담당한다.
/// 
/// 2023.05.22 LeHideKGIT
/// </summary>
class CPathManager
{
	SINGLE(CPathManager);
private:
	wchar_t		m_szContentPath[255];

public:
	void Initialize();
	const wchar_t* GetContentPath() { return m_szContentPath; }

};

