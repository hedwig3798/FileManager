#include "pch.h"
#include "CObject.h"

#include "CKeyManager.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "Animator.h"

// 기본 생성자
CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlibe(true)
	, m_bActive(true)
	, m_CollisionOn(true)
{
}

// 복사 생성자
// 복사 생성자의 경우 복사할 객체에 Collider와 Animator가 있으면
// 자신도 생성하지만 같은 Component를 사용할 것이 아니기 때문에 자신의 Component(Collider와 Animator)는 새로 메모리를 할당받아 생성한다
CObject::CObject(const CObject& _origin)
	: m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_strName(_origin.m_strName)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlibe(true)
	, m_bActive(true)
	, m_CollisionOn(true)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new Animator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (m_pCollider != nullptr)
		delete m_pCollider;
	
	if (m_pAnimator != nullptr)
		delete m_pAnimator;
}

void CObject::Finalupdate()
{
	// 개발자 모드에서 CollisionOn 설정
	if (m_pCollider != nullptr && m_CollisionOn)
	{
		m_pCollider->Finalupdate();
	}

	if (m_pAnimator != nullptr) 
	{
		m_pAnimator->FinalUpdate();
	}
}

void CObject::Render(HDC _dc)
{
	Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2), (int)(m_vPos.y - m_vScale.y / 2)
				 , (int)(m_vPos.x + m_vScale.x / 2), (int)(m_vPos.y + m_vScale.y / 2));
}

void CObject::ComponentRender(HDC _dc, bool _CollisionVisible)
{
	// 개발자 모드에서 CollisionVisible 설정
	if (m_pCollider != nullptr && _CollisionVisible)
	{
		m_pCollider->Render(_dc);
	}
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}
