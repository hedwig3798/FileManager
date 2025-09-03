#pragma once
#include "CUI.h"
class CEixtYesBtn :
    public CUI
{
public:
    CEixtYesBtn();
    ~CEixtYesBtn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
};

