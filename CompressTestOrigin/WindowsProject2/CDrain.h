#pragma once
#include "pch.h"
#include "CObject.h"
#include "Texture.h"
#include "TextureManager.h"

class CDrain
{
};



class CDrain :public CObject
{
public:

	//그림으로 쓸 텍스쳐
	Texture* m_DrainTexture[3];
	int m_iIndex;
	// 	//애니메이션으로 쓸 텍스쳐
	// 	Texture* m_pTextureAnimation;

	bool m_bIsOn;
	bool m_bIsPast;


	virtual void Update();
	virtual void Render(HDC _dc);
	//필수
	virtual CDrain* Clone() { return new CDrain(*this); }

public:
	CDrain();
	~CDrain();

};


