#pragma once
#include "CUI.h"
#include "Texture.h"
class Stage2_1Btn :
    public CUI
{
public:
	Stage2_1Btn();
	~Stage2_1Btn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
private:
	Texture* pStage2_1Btn;
};

