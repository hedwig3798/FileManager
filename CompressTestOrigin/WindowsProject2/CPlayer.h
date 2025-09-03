#pragma once
#include "CObject.h"
#include "Texture.h"
#include "CKeyManager.h"

class CPlayerState;

enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	ATTACK,
	MOVE_DELAY,
	ATTACK_DELAY,
	DEAD,
};

class CPlayer :
	public CObject
{
private:
    // 움직임 딜레이
	float m_fMoveDelay;
	float m_fAttackDelay;
	float m_fMoveMent;

	float m_fTimeLag;
	const float m_fMoveDelayRate = 0.5f;
	const float m_fTimeLagDelayRate = 0.2f;
	const float m_fAttackDelayRate = 0.5f;
	const float m_fDieDelayRate = 1.0f;

	const float m_fSlowRate = 0.8f;
	const float m_fSlowTime = 2.0f;
	float m_fDieDelay;

	

	bool m_bIsLeft;
	float m_bIsSlow;

	OBJECT_DIR m_eCurrDir;
	OBJECT_DIR m_eprevDir;
	bool m_bCanMove;

	POINT m_ptBoardPos;
	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePastState;

	//CPlayerState* m_pState;

	bool m_IsOverlap;
	

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void OnCollisionEnter(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);
    virtual CPlayer* Clone() { return new CPlayer(*this); }

	void SetMovement(float _fMovement) { m_fMoveMent = _fMovement; };
	static int m_siDeathCount;
	OBJECT_DIR GetDir() const
	{
		return m_eCurrDir;
	}
	void SetDir(OBJECT_DIR val)
	{
		m_eCurrDir = val;
	}
	POINT GetBoardPos() const
	{
		return m_ptBoardPos;
	}
	void SetBoardPos(POINT val)
	{
		m_ptBoardPos = val;
		SetPos(Vector2{ (int)((BOARD_TILE / 2) + (BOARD_TILE * val.x)),(int)(BOARD_TILE / 2 + (BOARD_TILE * val.y)) });
	}
private:
	void CreateMissile();
	void UpateState();
	void UpdateMove();
	void UpdateAnimation();

	bool CheckArrowKey() 
	{
		if (CKeyManager::GetInstance()->GetKeyState(KEY::UP) == KEY_STATE::HOLD ||
			CKeyManager::GetInstance()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD ||
			CKeyManager::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD ||
			CKeyManager::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	int m_iPoision;
	CPlayer();
	~CPlayer();
};