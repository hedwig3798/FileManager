#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;
public:
	void Update();
	void SetFocusedUI(CUI* _pUI);
	void ReStart();
	void Start();
	void MainMenu();
	void PlayerDio();
	void Continue();
private:
	// 부모 UI 내에서 실제로 타켓팅 된 UI 를 찾아서 반환한다. 
	CUI* GetTargetedUI(CUI* _pParentUI);
	CUI* GetFocusedUI();
};