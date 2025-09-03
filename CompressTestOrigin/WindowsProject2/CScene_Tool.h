#pragma once

#include <windows.h>
#include "CScene.h"     // TILE 클래스 ( 추가 : 이건재 )

/// <summary>
/// 실제로 구현 된 클래스
/// 
/// 씬을 만드는 씬.. 툴 씬
/// 
/// 2023.05.22 LeHide2Cam
/// </summary>
class CScene_Tool : public CScene
{
public:
    CScene_Tool(HWND hWnd, HDC hDC, POINT screenRes);
    ~CScene_Tool();

public:
    virtual void Update();
    virtual void Enter(bool _isPast);
    virtual bool Exit();

public:
    void SetTileIdx();

    void SaveTileData();
    void LoadTileDate();
    void SaveTile(const wstring& _strFilePath);

private:
    HWND m_hWnd;
    HDC m_hScreenDC;
    POINT m_ScreenRes;
};