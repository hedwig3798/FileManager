#pragma once
#include "CObject.h"
#include "Texture.h"

class Texture;

class CPoisonTile : public CObject
{
public:
	Texture* m_pTexture;
	
	bool	m_bIsOn;
	bool	m_bIsPast;

	void Update() override;
	void Render(HDC _dc) override;
	virtual CPoisonTile* Clone() { return (CPoisonTile*)this; }

	int m_iIndex;

public:
	Texture* pPoisonTexture[3];

public:
	CPoisonTile();
	~CPoisonTile();

};

