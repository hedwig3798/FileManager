#pragma once
#include "CObject.h"
class CUI :
	public CObject
{
private:
	vector<CUI*>	m_vecChildUI;
	CUI*			m_pParentUI;
	Vector2			m_vFinalPos;

	bool			m_bMouseOn;		// UI위에 마우스가 있는지
	bool			m_bLbtnDown;	// UI에 왼쪽버튼이 눌린적이 있는 지

public:
	Vector2 GetFinalPos() {return m_vFinalPos; }
	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn;  }
	bool IsLbtnDown() { return m_bLbtnDown; }

	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }
public:
	virtual void Update();
	virtual void Finalupdate();
	virtual void Render(HDC _dc);

private:
	void UpdateChild();
	void FinalupdateChild();
	void RenderChild(HDC _dc);
	
	void MouseOnCheck();

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnup();
	virtual void MouseLbtnClicked();


	virtual CObject* Clone(){ return new CUI(*this);}

public:
 	CUI();
	~CUI();

	friend class CUIMgr;
};