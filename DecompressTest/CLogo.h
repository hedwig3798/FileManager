#pragma once
#include "CUI.h"
#include "Texture.h"
class CLogo :
    public CUI
{
public: 
	CLogo();
	~CLogo();
public:
	virtual void Render(HDC _dc);
	virtual void Update();

private:
	Texture* pLogo;
};

