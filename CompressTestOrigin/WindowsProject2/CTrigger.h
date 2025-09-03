#pragma once
#include "CObject.h"
#include "pch.h"
#include "CTrap.h"
#include "CCollider.h"

class CTrap;
class CCollider;

class CTrigger :
    public CObject
{
public:
	CTrigger();
	~CTrigger();

	virtual void Update();
	// virtual void render(HDC _dc);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual CTrigger* Clone() { return new CTrigger(*this); }

	void AddTrap(CTrap* _trap);

private:
	vector<CTrap*> m_vecTraps;
};

