#pragma once
#include "CUI.h"
#include "Texture.h"
class Stage1_6Btn :
    public CUI
{
public:
    Stage1_6Btn();
    ~Stage1_6Btn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
private:
	Texture* pStage1_6Btn;
};

