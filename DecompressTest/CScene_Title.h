#pragma once
#include "CScene.h"
class CScene_Title :
    public CScene
{
public:
    CScene_Title(HWND hWnd, HDC hDC, POINT screenRes);
    ~CScene_Title();
public:
	virtual void Update();
	virtual void Enter(bool _isPast);
	virtual bool Exit();

private:
	
};

