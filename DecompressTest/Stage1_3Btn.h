#pragma once
#include "CUI.h"
#include "Texture.h"
class Stage1_3Btn :
    public CUI
{
public:
	Stage1_3Btn();
	~Stage1_3Btn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
private:
	Texture* pStage1_3Btn;
	
};

