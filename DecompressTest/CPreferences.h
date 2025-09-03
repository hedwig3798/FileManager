#pragma once
#include "CUI.h"
#include "Texture.h"
class CPreferences :
    public CUI
{
public:
    CPreferences();
    ~CPreferences();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	void Update();
	void Render(HDC _dc);
private:
	Texture* Preferences;

};

