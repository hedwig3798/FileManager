#pragma once
class CState
{
public:
	CState(PLAYER_STATE _eState);
/*	virtual ~CState();*/
	virtual void update() = 0;
	virtual void render(HDC _dc) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

private:
	PLAYER_STATE m_eStat;
};

