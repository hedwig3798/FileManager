#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
public:
	virtual void Enter(bool _isPast);
	virtual bool Exit();

public:
	CScene_Start(HWND hWnd, HDC hDC, POINT screenRes);
	~CScene_Start();
};
