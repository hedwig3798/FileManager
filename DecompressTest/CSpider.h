#pragma once
#include "CMonster.h"
//#include "CResMgr.h"
#include "TextureManager.h"

#include "CScene.h"

class CScene;
class Texture;

class CSpider :
    public CMonster
{
public:
	CSpider();
	~CSpider();
	virtual void Update();
	virtual CSpider* Clone() { return new CSpider(*this); }
	virtual void Render(HDC _dc);   
	void SetBoardPos(POINT _pt) { m_ptBoardPos = _pt; }

private:
	Texture* m_mTex;   

private:
	// 움직임 딜레이
	float m_fMoveDelay;
	float m_fMoveMent;

	const float m_fMoveDelayRate = 0.5f;

	Vector2 m_vChasePos;

	OBJECT_DIR m_eCurrDir;
	OBJECT_DIR m_ePrevDir;
	bool m_bCanMove;

	POINT m_ptBoardPos;
	MONSTER_STATE m_eCurrState;
	MONSTER_STATE m_ePrevState;
	
	void UpateState();
	void UpdateMove();
	void UpdateAnimation();

	virtual void OnCollisionEnter(CCollider* _pOther);
};

