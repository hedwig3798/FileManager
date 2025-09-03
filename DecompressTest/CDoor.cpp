#include "pch.h"
#include "CDoor.h"

#include "CCollider.h"
#include "Animator.h"
#include "Animation.h"

#include "TextureManager.h"
#include "Texture.h"

#include "CSceneManager.h"
#include "CScene.h"


CDoor::CDoor()
	: IsOpen(false)
	, Once(true)
	, Pos()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(120.f, 120.f));

	Texture* pTexture = TextureManager::GetInstance()->LoadTexture(L"Door", L"texture\\door.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Prev_Door_Close", pTexture, Vector2(0.f, 0.f), Vector2(60.f, 120.f), Vector2(0.f, 0.f), 1.f, 1);
	GetAnimator()->CreateAnimation(L"Prev_Door_Open", pTexture, Vector2(100.f, 0.f), Vector2(20.f, 120.f), Vector2(0.f, 0.f), 1.f, 1);

	GetAnimator()->CreateAnimation(L"Current_Door_Close", pTexture, Vector2(120.f, 0.f), Vector2(60.f, 120.f), Vector2(0.f, 0.f), 1.f, 1);
	GetAnimator()->CreateAnimation(L"Current_Door_Open", pTexture, Vector2(220.f, 0.f), Vector2(20.f, 120.f), Vector2(0.f, 0.f), 1.f, 1);

	GetAnimator()->Play(L"Current_Door_Close", true);
}

CDoor::~CDoor()
{
}

void CDoor::Update()
{
	if (Once)
	{
		Once = false;
		Pos = GetPos();
	}

	if (IsOpen == true && (CSceneManager::GetInstance()->GetCurScene()->m_bIsPast) == false)
	{
		GetAnimator()->Play(L"Current_Door_Open", true);
		
		Vector2 MovePos = Pos;
		MovePos.x -= 20;

		SetPos(MovePos);
	}
	else if (IsOpen == false && (CSceneManager::GetInstance()->GetCurScene()->m_bIsPast) == false)
	{
		GetAnimator()->Play(L"Current_Door_Close", true);

		Vector2 MovePos = Pos;

		SetPos(MovePos);
	}

	if (IsOpen == true && (CSceneManager::GetInstance()->GetCurScene()->m_bIsPast) == true)
	{
		GetAnimator()->Play(L"Prev_Door_Open", true);

		Vector2 MovePos = Pos;
		MovePos.x -= 20;

		SetPos(MovePos);
	}
	else if (IsOpen == false && (CSceneManager::GetInstance()->GetCurScene()->m_bIsPast) == true)
	{
		GetAnimator()->Play(L"Prev_Door_Close", true);

		Vector2 MovePos = Pos;

		SetPos(MovePos);
	}
}

void CDoor::Render(HDC _dc)
{
}
