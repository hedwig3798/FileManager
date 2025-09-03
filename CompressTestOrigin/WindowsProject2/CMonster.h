#pragma once
#include "CObject.h"
#include "CSceneManager.h"

class Texture;

class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void Update();
    virtual CMonster* Clone() { return new CMonster(*this); }
	virtual void Render(HDC _dc);  
};