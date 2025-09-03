#pragma once
#include "CUI.h"
#include "Texture.h"
class CGameEixt :
    public CUI
{
public:
    CGameEixt();
    ~CGameEixt();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
	int m_iMousecheck;
private:
	Texture* pEixt;
	Texture* pEixtOn;

	Texture* pNowEixt;
};

