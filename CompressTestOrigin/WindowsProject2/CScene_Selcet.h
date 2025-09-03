#pragma once
#include "CScene.h"
class CScene_Selcet :
    public CScene
{
public:
	CScene_Selcet(HWND hWnd, HDC hDC, POINT screenRes);
	~CScene_Selcet();

public:
	virtual void Update();
	virtual void Enter(bool _isPast);
	virtual bool Exit();
};

