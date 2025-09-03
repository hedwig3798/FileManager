#pragma once
#include "CObject.h"


class CLever :
	public CObject
{
private:
	int TriggerNumber;
	bool LeverOnOff;
	bool IsCurrent;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void TurnTime();

public:
	int GetTriggerNumber() { return TriggerNumber; }
	void SetTriggerNumber(int _TriggerNumber) { TriggerNumber = _TriggerNumber; }

	// 오브젝트 복사할 때 필요한 함수 ( 순수 가상 함수, 자식 클래스에서 구현 필요 )
	virtual CLever* Clone() { return this; }

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	bool m_bIsPast;

public:
	CLever(bool _isPast);
	~CLever();
};