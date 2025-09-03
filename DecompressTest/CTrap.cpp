#include "pch.h"
#include "CTrap.h"

CTrap::CTrap()
	: m_bTriggered(false)
	, m_pTrigger(nullptr)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));
	GetCollider()->SetScale(Vector2(0.f, 0.f));
}

CTrap::~CTrap()
{
}

void CTrap::Update()
{
}

void CTrap::Render(HDC _dc)
{
}

void CTrap::OnCollision(CCollider* _pOther)
{
}

void CTrap::OnCollisionEnter(CCollider* _pOther)
{
	// 플레이어 죽음 처리
}

void CTrap::OnCollisionExit(CCollider* _pOther)
{
}
