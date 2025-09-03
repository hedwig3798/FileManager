#pragma once
#include "pch.h"
#include "CObject.h"
class Tile : public CObject
{
public:
	Tile();
	virtual ~Tile();
	virtual void update();
	void render(HDC _dc);
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

};

