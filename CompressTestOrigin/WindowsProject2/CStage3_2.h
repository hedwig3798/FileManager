#pragma once
#include "CScene.h"
class CStage3_2 :
    public CScene
{
public:
	CStage3_2(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage3_2();

	void Enter(bool _isPast) override;

	bool Exit() override;
};

