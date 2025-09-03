#pragma once
#include "CUI.h"
#include "Texture.h"
class Stage1_8Btn :
    public CUI
{
public:
	Stage1_8Btn();
	~Stage1_8Btn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
private:
	Texture* pStage1_8Btn;
};

