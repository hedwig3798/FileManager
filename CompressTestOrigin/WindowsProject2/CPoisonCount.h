#pragma once
#include "CUI.h"
#include "Texture.h"


class CPoisonCount :
    public CUI
{
public:
    CPoisonCount();
    ~CPoisonCount();
	virtual void Update();
	virtual CPoisonCount* Clone() { return new CPoisonCount(*this); }
	void Render(HDC _dc);

private:

	Texture* pPoisonCount;
	Texture* pPoisonCount1;
	Texture* pPoisonCount2;
	Texture* pPoisonCount3;

	Texture* pNowPoisonCount;

	int m_iPosionCount;
};

