#pragma once
#include "CScene.h"

class CCutScene : public CScene
{
public:
	virtual void Enter(bool _isPast) ;
	virtual bool Exit();
	virtual void Update();

public:
	CCutScene(HWND hWnd, HDC hDC, POINT screenRes);		
	~CCutScene();
};

