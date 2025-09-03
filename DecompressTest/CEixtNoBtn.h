#pragma once
#include "CUI.h"
class CEixtNoBtn :
    public CUI
{
public:
    CEixtNoBtn();
    ~CEixtNoBtn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
};

