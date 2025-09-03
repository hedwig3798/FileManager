#pragma once
#include "CUI.h"
#include "Texture.h"
class StageBtn :
    public CUI
{
public:
	StageBtn(int i, int j);
	~StageBtn();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
private:
	Texture* pStageBtn;
	Texture* pStageStage;
	Texture* pStageRoom;
	Texture* pMinus;
	int i;
	int j;
};

