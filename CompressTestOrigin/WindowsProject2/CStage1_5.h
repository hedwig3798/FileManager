#pragma once
#include "CScene.h"
class CStage1_5 :
    public CScene
{
public:
	CStage1_5(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage1_5();

	void Enter(bool _isPast) override;

	bool Exit() override;

};

