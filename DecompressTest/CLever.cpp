#include "pch.h"
#include "CLever.h"
#include "CCollider.h"

#include "TextureManager.h"
#include "CKeyManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"

#include "CSceneManager.h"
#include "CScene.h"

CLever::CLever(bool _isPast)
	:TriggerNumber(0)
	, LeverOnOff(false)
	, IsCurrent(true)
	, m_bIsPast(_isPast)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(50.f, 50.f));
	GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));

	Texture* pTexture = TextureManager::GetInstance()->LoadTexture(L"Lever", L"texture\\rever.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Prev_Lever_On", pTexture, Vector2(0.f, 0.f), Vector2(64.f, 64.f), Vector2(64.f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"Prev_Lever_Off", pTexture, Vector2(128.f, 0.f), Vector2(64.f, 64.f), Vector2(-64.f, 0.f), 0.3f, 1);

	GetAnimator()->CreateAnimation(L"Current_Lever_On", pTexture, Vector2(0.f, 64.f), Vector2(64.f, 64.f), Vector2(64.f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"Current_Lever_Off", pTexture, Vector2(128.f, 64.f), Vector2(64.f, 64.f), Vector2(-64.f, 0.f), 0.3f, 1);

	if (m_bIsPast)
	{
		GetAnimator()->Play(L"Current_Lever_Off", true);
	}
	else
	{
		GetAnimator()->Play(L"Prev_Lever_Off", true);
	}
}

CLever::~CLever()
{
}

void CLever::Update()
{
}

void CLever::Render(HDC _dc)
{
	if (!m_bIsPast == true && LeverOnOff == false)
	{
		GetAnimator()->Play(L"Current_Lever_Off", true);
	}
	else if (!m_bIsPast == true && LeverOnOff == true)
	{
		GetAnimator()->Play(L"Current_Lever_On", true);
	}
	else if (!m_bIsPast == false && LeverOnOff == false)
	{
		GetAnimator()->Play(L"Prev_Lever_Off", true);
	}
	else if (!m_bIsPast == false && LeverOnOff == true)
	{
		GetAnimator()->Play(L"Prev_Lever_On", true);
	}
}

// 시간이 바뀔 때마다 레버 애니메이션 변경
void CLever::TurnTime()
{

}

// 플레이어가 레버를 작동 시킬 경우에 애니메이션 및 Trigger 이벤트 호출
void CLever::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Whip_Player")
	{
		LeverTriggerOn(this);		///분명 func.h는 위에 헤더파일에 명시되지않았는데.. 어째서 가능??? -> pch.h에 있기 때문에 가능하다

		if (LeverOnOff)
			LeverOnOff = false;
		else
			LeverOnOff = true;
	}
}