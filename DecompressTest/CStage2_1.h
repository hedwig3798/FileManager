#pragma once
#include "CScene.h"
class CStage2_1 :
    public CScene
{
public:
	CStage2_1(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage2_1();

	void Enter(bool _isPast) override;

	bool Exit() override;
};

