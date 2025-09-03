#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CGameProcess.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

// 콜라이더의 복사 생성자가 호출될 경우에 ID는 같은 ID를 가질 수 없기에 따로 복사 생성자 작성
CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{

}

CCollider::~CCollider()
{
}

void CCollider::Finalupdate()
{
	// Object의 위치를 따라간다.
	Vector2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void CCollider::Render(HDC _dc)
{
// 	PEN_TYPE ePen = PEN_TYPE::GREEN;
// 
// 	if (m_iCol)
// 		ePen = PEN_TYPE::RED;

	HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HBRUSH hollowBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	HPEN defaultPen = (HPEN)SelectObject(_dc, greenPen);
	HBRUSH defaultBrush = (HBRUSH)SelectObject(_dc, hollowBrush);
	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));

	SelectObject(_dc, defaultPen);
	SelectObject(_dc, defaultBrush);

	DeleteObject(greenPen);
	DeleteObject(hollowBrush);
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	m_iCol--;
	m_pOwner->OnCollisionExit(_pOther);
}
