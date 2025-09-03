#pragma once
#include "CUI.h"
#include "CPanelUI.h"
#include "Texture.h"
class CBtnUI:
	public CUI
{
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
public:
	CBtnUI();
	~CBtnUI();
private:
	Texture* pBtnUI;
};

