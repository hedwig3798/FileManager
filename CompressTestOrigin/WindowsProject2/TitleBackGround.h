#pragma once
#include "CObject.h"
#include "Texture.h"
class CTexture;

class TitleBackGround 
	: public CObject
{
public:
	TitleBackGround();
	~TitleBackGround();
	virtual void Update();
	virtual TitleBackGround* Clone() { return new TitleBackGround(*this); }
	
	void Render(HDC _dc);

private:
	Texture* pBackGround;
};

