#pragma once
#include "CUI.h"
#include "Texture.h"
class CClock :
    public CUI
{
public:
    CClock();
    ~CClock();
    void Render(HDC _dc);

private:
    Texture* pClock;
};

