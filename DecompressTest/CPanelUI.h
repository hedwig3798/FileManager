#pragma once
#include "CUI.h"
#include "Texture.h"
class CPanelUI :
	public CUI
{
public:
	CPanelUI();
	~CPanelUI();

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void Render(HDC _dc);
	virtual void Update();
	int m_iMousecheck;

private:
	Vector2		m_vDragStart; 

private:
	Texture* pPanelUI;
	Texture* pPanelUIOn;

	Texture* pNowPanelUI;
};

