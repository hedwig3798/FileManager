#include "pch.h"
#include "StageRelics.h"
// 텍스처
#include "TextureManager.h"
#include "Texture.h"
// 애니메이션 
#include "Animation.h"
#include "Animator.h"
//충돌체크
#include "CCollisionManager.h"
#include "CCollider.h"
// 
#include "CUI.h"
#include "CStone.h"

StageRelics::StageRelics():
	m_ptBoardPos{}
{
	Texture* pStageRelics = TextureManager::GetInstance()->LoadTexture(L"StageRelics", L"texture\\relic.bmp");

	//Animaton 세팅하기
	CreateAnimator();
	//Relic Anmation
	GetAnimator()->CreateAnimation(L"StageRelics", pStageRelics, Vector2(0.f,0.f),Vector2(200.f,200.f), Vector2(200.f,0.f), 0.3f, 10, 0.75f);
	GetAnimator()->Play(L"StageRelics", true);
	//Collider 세팅하기
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2(0.f, 5.f));
	GetCollider()->SetScale(Vector2(100.f, 100.f));
}

StageRelics::~StageRelics()
{

}

void StageRelics::Update()
{	


	GetCollider()->SetScale(Vector2(100.f, 100.f));
		
}

void StageRelics::Render(HDC _dc)
{

}

void StageRelics::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Whip_Player")
	{
		Vector2 vResoulution = Vector2(1920, 1080);
		Vector2 Stone = Vector2(300.f, 200.f);

		CUI* pStone_Cur = new CStone(false);
		pStone_Cur->SetName(L"Stone_Cur");
		pStone_Cur->SetScale(Stone);
		pStone_Cur->SetPos(Vector2((vResoulution.x / 2) - (pStone_Cur->GetScale().x / 2 + 10.0f), 20.f));
		pStone_Cur->m_bActive = true;
		CreateObject(pStone_Cur, GROUP_TYPE::Event_UI);

		CUI* pStone_Past = new CStone(true);
		pStone_Past->SetName(L"Stone_Past");
		pStone_Past->SetScale(Stone);
		pStone_Past->SetPos(Vector2((vResoulution.x / 2) - (pStone_Past->GetScale().x / 2 + 10.0f), 20.f));
		pStone_Past->m_bActive = false;
		CreateObject(pStone_Past, GROUP_TYPE::Event_UI);
		DeleteObject(this);
	}
}

