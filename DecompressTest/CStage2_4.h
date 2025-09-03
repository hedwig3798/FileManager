#pragma once
#include "CScene.h"
class CStage2_4 :
    public CScene
{
public:
	CStage2_4(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage2_4();
	void Enter(bool _isPast) override;
	bool Exit() override;
};

