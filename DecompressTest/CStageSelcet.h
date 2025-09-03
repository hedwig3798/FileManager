#pragma once
#include "CUI.h"
#include "Texture.h"
class CStageSelcet :
    public CUI
{
public:
	CStageSelcet();
	~CStageSelcet();
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
	int m_iMousecheck;
private:
	Texture* StageSelcetOn;
	Texture* StageSelcet;

	Texture* NowStageSelcet;
};

