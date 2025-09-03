#pragma once
#include "CUI.h"
class CReStart :
	public CUI
{
public:
	CReStart();
	~CReStart();

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
};

