#pragma once
#include "CUI.h"
#include "Texture.h"
class Stage1_4Btn :
    public CUI
{
public:
	Stage1_4Btn();
	~Stage1_4Btn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
private:
	Texture* pStage1_4Btn;
};

