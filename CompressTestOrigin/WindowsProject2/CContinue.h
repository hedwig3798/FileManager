#pragma once
#include "CUI.h"
#include "CPreferences.h"

class CContinue :
    public CUI
{
public:
    CContinue();
    ~CContinue();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
};

