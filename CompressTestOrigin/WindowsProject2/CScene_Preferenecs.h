#pragma once
#include "CScene.h"
class CScene_Preferenecs :
    public CScene
{
public:
    CScene_Preferenecs(HWND hWnd, HDC hDC, POINT screenRes);
    ~CScene_Preferenecs();
public:
	virtual void Update();
	virtual void Enter(bool _isPast);
	virtual bool Exit();
};

