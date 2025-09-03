#pragma once
#include "CUI.h"
#include "Texture.h"
class CGameStart :
    public CUI
{
public:
	CGameStart();
	~CGameStart();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
	int m_iMousecheck;
private:
	Texture* pGamestart;
	Texture* pGamestarton;
	
	Texture* pNowgame;
};

