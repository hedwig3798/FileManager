#pragma once
#include "CObject.h"
#include "CTrigger.h"
#include "pch.h"

class CTrigger;
class CCollider;

class CTrap :
    public CObject
{
public:
    CTrap();
    ~CTrap();

    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
	virtual CTrap* Clone() { return new CTrap(*this); }

    bool GetTriggered() const
    {
        return m_bTriggered;
    }
    void SetTriggered(bool val)
    {
        m_bTriggered = val;
    }
private:
    bool m_bTriggered;
    CTrigger* m_pTrigger;
};

