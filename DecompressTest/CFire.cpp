///fire가 4방향에서 나오니까 애니메이션 4개가 필요하다(플레이어 기준으로 fire trap이 있는 방향을 up, down, left, right 나누었다
///크기는 애니메이션 만들 때 바꿀 수 있으니까, 4방향 애니메이션 만든다
#include "pch.h"
#include "CFire.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "SelectGDI.h"

CFire::CFire(OBJECT_DIR _dir)				// 추가
	: m_fTheta((float)PI / 2.f)
	, m_dir(_dir)							// 추가
	, m_fLifeTiem(5.5f)
	, TriggerOn(true)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2(0.f, 0.f));


	switch (m_dir)							// 추가
	{
	case OBJECT_DIR::UP:
	{
		//down: 불이 플레이어의 아래에서 나온다
		Texture* pFireTexture4 = TextureManager::GetInstance()->LoadTexture(L"fire_down", L"texture\\fire_down.bmp");	//down에서 나오는 불
		CreateAnimator();
		GetAnimator()->CreateAnimation(L"FIRE_1_DOWN_START", pFireTexture4, Vector2(0.f, 0.f), Vector2(120.0f, 240.f), Vector2(120.0f, 0.f), 0.2f, 2);
		GetAnimator()->CreateAnimation(L"FIRE_1_DOWN_LOOP", pFireTexture4, Vector2(120.0f * 2, 240.f + 1), Vector2(120.0f, 240.f), Vector2(120.0f, 0.f), 0.2f, 4);
		GetAnimator()->Play(L"FIRE_1_DOWN_LOOP", true);
	}
	break;
	case OBJECT_DIR::LEFT:
	{
		////right: 불이 플레이어의 오른쪽에서 나온다
		Texture* pFireTexture3 = TextureManager::GetInstance()->LoadTexture(L"fire_right", L"texture\\fire_right.bmp");	//right에서 나오는 불
		CreateAnimator();
		GetAnimator()->CreateAnimation(L"FIRE_1_RIGHT_START", pFireTexture3, Vector2(0.f, 0.f), Vector2(240.0f, 120.f), Vector2(0.f, 120.f), 0.2f, 2);
		GetAnimator()->CreateAnimation(L"FIRE_1_RIGHT_LOOP", pFireTexture3, Vector2(240.f + 1.f, 120.f * 2), Vector2(240.0f - 1.f, 120.f), Vector2(0.f, 120.f), 0.2f, 4);
		GetAnimator()->Play(L"FIRE_1_RIGHT_LOOP", true);
	}
	break;
	case OBJECT_DIR::RIGHT:
	{
		//left: 불이 플레이어의 왼쪽에서 나온다
		Texture* pFireTexture2 = TextureManager::GetInstance()->LoadTexture(L"fire_left", L"texture\\fire_left.bmp");	//left에서 나오는 불
		CreateAnimator();
		GetAnimator()->CreateAnimation(L"FIRE_1_LEFT_START", pFireTexture2, Vector2(0.f, 0.f), Vector2(240.0f, 120.f), Vector2(0.f, 120.f), 0.2f, 2);
		GetAnimator()->CreateAnimation(L"FIRE_1_LEFT_LOOP", pFireTexture2, Vector2(0.0f, 120.f * 2), Vector2(240.0f, 120.f), Vector2(0.f, 120.f), 0.2f, 4);
		GetAnimator()->Play(L"FIRE_1_LEFT_LOOP", true);
	}
	break;
	case OBJECT_DIR::DOWN:
	{
		//up: 불이 플레이어의 위에서 나온다
		Texture* pFireTexture1 = TextureManager::GetInstance()->LoadTexture(L"fire_up", L"texture\\fire_up.bmp");	//up에서 나오는 불
		CreateAnimator();
		GetAnimator()->CreateAnimation(L"FIRE_1_UP_START", pFireTexture1, Vector2(0.f, 0.f), Vector2(120.0f, 240.f), Vector2(120.0f, 0.f), 0.2f, 2);
		GetAnimator()->CreateAnimation(L"FIRE_1_UP_LOOP", pFireTexture1, Vector2(120.0f * 2, 0.f), Vector2(120.0f, 240.f), Vector2(120.0f, 0.f), 0.2f, 4);
		GetAnimator()->Play(L"FIRE_1_UP_LOOP", true);
	}
	break;
	}
	///생성자에서 Update, Render하지않는다. 생성자에서는 4방향 중 하나를 선택하고, 생성자 밖에서 Update, Render 한다
}

CFire::~CFire()
{
}

void CFire::Update()
{
	Vector2 vScale = GetScale();

	GetCollider()->SetScale(vScale);
}

void CFire::Render(HDC _dc)
{

}

void CFire::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
