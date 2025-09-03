#pragma once
#include "CScene.h"
class CStage1_7 :
    public CScene
{
public:
	CStage1_7(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage1_7();

	void Enter(bool _isPast) override;

	bool Exit() override;

};

