#pragma once
#include "pch.h"
#include "CObject.h"
#include "Texture.h"
#include "TextureManager.h"


class EmptyObject :public CObject
{
public:
	
	//그림으로 쓸 텍스쳐
	Texture* m_pTexture;

	virtual void Update();
	virtual void Render(HDC _dc);
	//필수
	virtual EmptyObject* Clone() { return new EmptyObject(*this); }
	int m_iIndex;
public:
	EmptyObject();
	~EmptyObject();

};

