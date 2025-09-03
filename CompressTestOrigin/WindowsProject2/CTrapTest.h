#pragma once
#include "CScene.h"
#include "CObject.h"
class CObject;
class CTrapTest :
    public CScene
{
public:
	virtual void Update();
	virtual void Enter(bool _isPast);
	virtual bool Exit();

public:
	CTrapTest(HWND hWnd, HDC hDC, POINT screenRes);
	~CTrapTest();
};

