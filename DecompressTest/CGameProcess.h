#pragma once

#include "pch.h"

/// <summary>
/// 게임 진행을 담당함
/// 
/// 가장 큰 틀을 이루는 클래스
/// 
/// 2023.05.22 LeHide2Cam1CSCREEN
/// </summary>
class CGameProcess
{
public:
	CGameProcess();
	~CGameProcess();

public:
	int Initialize(HWND _hWnd, POINT _ptResoultion);
	void Progress();

public:
	HWND GetMainHWnd() { return m_hWnd; }


	/// ///////////////////////////////////////////////////////////////////////
	/// 이 아래 부분은 Graphics Engine으로 가야 할 듯.
	/// TODO:LEHIDE
private:
	void CreateBrushPen();

public:
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

private:
	HWND	m_hWnd;					// 메인 윈도우 핸들
	POINT	m_ptResolution;			// 메인 윈도우 해상도
	HDC		m_hDC;					/// 스크린 DC (화면)

	HBITMAP	m_hBit;
	HDC		m_memDC;

	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];
	/// ///////////////////////////////////////////////////////////////////////
};