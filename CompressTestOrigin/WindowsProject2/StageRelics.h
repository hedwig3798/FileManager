#pragma once
#include "CObject.h"
class StageRelics : public CObject
{
public:
	StageRelics();
	~StageRelics();

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual StageRelics* Clone() { return this; }

	void SetBoardPos(POINT val)
	{
		m_ptBoardPos = val;
	}


	
private:
	POINT m_ptBoardPos;

private:
	// 콜리전 이벤트 발생
	virtual void OnCollisionEnter(CCollider* _pOther);
};

