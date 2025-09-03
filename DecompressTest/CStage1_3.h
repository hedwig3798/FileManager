#pragma once
#include "CScene.h"
class CStage1_3 :
    public CScene
{
public:
	CStage1_3(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage1_3();
	void Enter(bool _isPast) override;
	bool Exit() override;
};

