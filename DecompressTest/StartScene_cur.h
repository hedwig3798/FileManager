#pragma once
#include "pch.h"
#include "CScene.h"

class StartScene_cur
	: public CScene
{
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
	StartScene_cur();
	~StartScene_cur();
};

