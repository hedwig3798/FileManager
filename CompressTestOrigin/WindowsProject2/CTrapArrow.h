#pragma once
#include "CTrap.h"
#include "CMissile.h"



class Texture;

class CMissile;

class CTrapArrow :
    public CTrap
{
public:
	virtual void Update();
	virtual void Render(HDC _dc);
	void CreateMissile();
	OBJECT_DIR GetDir()
	{
		return m_dir;

	}
	void SetDir(OBJECT_DIR _dir)
	{
		_dir = m_dir;
	}
	virtual CTrapArrow* Clone() { return new CTrapArrow(*this); }

private:
	OBJECT_DIR m_dir;
	float m_fAttackSpeed;
	int m_AttackCount;


public:
	CTrapArrow();
	~CTrapArrow();
};

