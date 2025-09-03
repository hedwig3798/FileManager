#pragma once
#include "CScene.h"
class CStage2_6 :
    public CScene
{
public:
	CStage2_6(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage2_6();

	void Enter(bool _isPast) override;

	bool Exit() override;
};
