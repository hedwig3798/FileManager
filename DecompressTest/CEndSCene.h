#pragma once
#include "CScene.h"

class CEndSCene :public CScene
{
public:
	virtual void Enter(bool _isPast);
	virtual bool Exit();
	virtual void Update();

public:
	CEndSCene(HWND hWnd, HDC hDC, POINT screenRes);
	~CEndSCene();

};

