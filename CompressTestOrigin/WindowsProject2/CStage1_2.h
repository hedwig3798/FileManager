#pragma once
#include "pch.h"
#include "CScene.h"

class CStage1_2 : public CScene
{
public:
	CStage1_2(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage1_2();

	void Enter(bool _isPast) override;

	bool Exit() override;
};

