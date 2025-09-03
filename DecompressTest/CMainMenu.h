#pragma once
#include "CUI.h"
#include "Texture.h"
class CMainMenu :
    public CUI
{

public:
    CMainMenu();
    ~CMainMenu();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
	int m_iMousecheck;

private:
	Texture* pMainMenu;
	Texture* pMainMenuOn;

	Texture* pNowMainMenu;
};

