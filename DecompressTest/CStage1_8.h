#pragma once
#include "CScene.h"
class CStage1_8 :
    public CScene
{
public:
	CStage1_8(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage1_8();
	void Enter(bool _isPast) override;
	bool Exit() override;
};

