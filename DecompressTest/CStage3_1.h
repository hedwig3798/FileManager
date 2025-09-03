#pragma once
#include "CScene.h"
class CStage3_1 :
    public CScene
{
public:
	CStage3_1(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage3_1();

	void Enter(bool _isPast) override;

	bool Exit() override;
};

