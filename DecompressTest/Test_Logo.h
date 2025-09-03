#pragma once
#include "CUI.h"
#include "Texture.h"
class Test_Logo :
    public CUI
{
public:
    Test_Logo();
    ~Test_Logo();

public:
	virtual void Update();
	virtual Test_Logo* Clone() { return new Test_Logo(*this); }
	void Render(HDC _dc);

private:
	Texture* pTextLogo;
};

