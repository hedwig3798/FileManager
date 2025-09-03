#pragma once
#include "CMonster.h"
#include "Texture.h"
#include "CScene.h"
class Texture;
class Cscene;
enum class MONSTER_STATE_G
{
	IDLE,
	PATROL,
	ATTACK,
	PATROL_DELAY,
	ATTACK_DELAY,
	STUN
};

class CGuardian :
    public CMonster
{
public:
	CGuardian();
	~CGuardian();
	virtual void Update();
	virtual CGuardian* Clone() { return new CGuardian(*this); }
	virtual void Render(HDC _dc);   //요기 추가- 성균
	void SetBoardPos(POINT _pt) { m_ptBoardPos = _pt; }

	void SetCenter(POINT val)
	{
		m_ptCenter = val;
	}
	void SetIsHorizen(bool val)
	{
		m_bIsHorizen = val;
	}
	void SetMoveRange(int val)
	{
		m_iMoveRange = val;
	}
	void SetCanMove(bool val)
	{
		m_bCanMove = val;
	}
private:
	Texture* m_mTex;   
	bool m_bIsHorizen;
private:
	// 움직임 딜레이
		// 움직임 딜레이
	float m_fMoveDelay;
	float m_fAttackDelay;
	float m_fMoveMent;
	int m_iMoveRange;
	int m_iMovePoint;
	bool m_bIsLeft;
	const float m_fMoveDelayRate = 0.5f;
	const float m_fAttackDelayRate = 0.5f;

	float m_fStunDelay;

	const float m_fStunDelayRate = 10.0f;

	bool m_bCanMove;

	OBJECT_DIR m_eAttackDir;

	POINT m_ptBoardPos;
	POINT m_ptCenter;
	MONSTER_STATE_G m_eCurrState;

	void UpateState();
	void UpdateMove();
	void UpdateAnimation();

	void CreateMissile();

	virtual void OnCollisionEnter(CCollider* _pOther);
};

