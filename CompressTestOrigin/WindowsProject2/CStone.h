#pragma once
#include "CUI.h"
#include "Texture.h"

class Texture;

class CStone :
    public CUI
{

public:
    CStone(bool _isPast);  // 持失切 
    ~CStone(); // 社瑚切

public:
    virtual void Render(HDC _dc);
    virtual void Update();
    int Pos ;
private:
    Texture* pStone1;
    Texture* pStone2;
    bool m_bIsPast;
    Texture* pNowStone;
};


