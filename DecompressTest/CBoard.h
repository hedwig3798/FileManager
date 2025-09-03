#pragma once
#include "pch.h"
#include "CObject.h"
class CBoard
	: public CObject
{
public:
	CBoard();
	~CBoard();

	virtual void Update();
	virtual void render(HDC _dc);
	virtual CObject* Clone()
	{
		return new CBoard(*this);
	}
};

