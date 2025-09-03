#pragma once
#include "CUI.h"
#include "Texture.h"
#include "CPlayer.h"
class CClockConut :
    public CUI
{
public:
    CClockConut();
    ~CClockConut();

public:
    void Render(HDC _dc);
    virtual CClockConut* Clone() { return this; }
    virtual void Update();
private:
    Texture* pClockConut[11];

    string m_szStringDeatchCount;
    Texture* pNowClockCount;
    int m_iClockConut;
    int m_iClockconutTen;
    int m_PlayDead;
};

