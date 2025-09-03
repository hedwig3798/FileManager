#include "pch.h"
#include "CWhip.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "SoundManager.h"

CWhip::CWhip(bool _isLeft) : m_fTheta((float)PI / 2.f)
, m_dir{}
, m_fLifeTiem(0.5f)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(240.f, 240.f));

	Texture* pRightTexture = TextureManager::GetInstance()->LoadTexture(L"Attack_Effect_Right", L"texture\\attack_effect_right.bmp");
	Texture* pLeftTexture = TextureManager::GetInstance()->LoadTexture(L"Attack_Effect_Left", L"texture\\attack_effect_left.bmp");
	CreateAnimator();

	// ÀüÃ¼ 154 x 143 / " 146 x 137
	GetAnimator()->CreateAnimation(L"ATTACK_EFFECT_LEFT", pLeftTexture, Vector2(150.0f * 2, 0.f), Vector2(150.0f, 44.0f), Vector2(-150.0f, 0.f), m_fLifeTiem / 3, 3, 0.5);
	GetAnimator()->CreateAnimation(L"ATTACK_EFFECT_RIGHT", pRightTexture, Vector2(0.f, 0.f), Vector2(150.0f, 44.0f), Vector2(150.0f, 0.f), m_fLifeTiem / 3, 3, 0.5);
	if (_isLeft)
	{
		GetAnimator()->Play(L"ATTACK_EFFECT_LEFT", false);
	}
	else
	{
		GetAnimator()->Play(L"ATTACK_EFFECT_RIGHT", false);

	}
	SoundManager::GetInstance()->Play(PLAYER_ATTACK, EFFECT);
}

CWhip::~CWhip()
{
}

void CWhip::Update()
{
	m_fLifeTiem -= CTimeManager::GetInstance()->GetfDT();
	if (m_fLifeTiem <= 0)
	{
		DeleteObject(this);
	}

	Vector2 vPos = GetPos();

	SetPos(vPos);
}

void CWhip::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	//ComponentRender(_dc);
}

void CWhip::OnCollisionEnter(CCollider* _pOther)
{
}
