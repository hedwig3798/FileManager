#pragma once
#include "CScene.h"
class CStage2_2 :
    public CScene
{
public:
	CStage2_2(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage2_2();
	void Enter(bool _isPast) override;
	bool Exit() override;
};

