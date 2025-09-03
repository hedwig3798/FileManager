#pragma once
#include "CUI.h"
class CGameExit :
    public CUI
{
public:
    CGameExit();
    ~CGameExit();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();

};

