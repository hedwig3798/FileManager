#pragma once
#include "CScene.h"
class CStage2_3 :
    public CScene
{
public:
	CStage2_3(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage2_3();
	void Enter(bool _isPast) override;
	bool Exit() override;
};

