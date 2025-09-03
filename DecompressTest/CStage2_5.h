#pragma once
#include "CScene.h"
class CStage2_5 : public CScene
{
public:
	CStage2_5(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage2_5();

	void Enter(bool _isPast) override;

	bool Exit() override;
};

