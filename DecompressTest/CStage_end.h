#pragma once
#include "CScene.h"
class CStage_end :
    public CScene
{
public:
	CStage_end(HWND hWnd, HDC hDC, POINT screenRes);
	~CStage_end();

	void Enter(bool _isPast) override;

	bool Exit() override;
};

