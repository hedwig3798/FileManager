#pragma once
#include "CUI.h"
#include "Texture.h"
class CPoison :
    public CUI
{
public:
    CPoison();
    ~CPoison();
    void Render(HDC _dc);

private:
    Texture* pPoison;
};

