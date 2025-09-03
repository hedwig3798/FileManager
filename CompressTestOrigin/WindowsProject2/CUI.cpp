#include "pch.h"
#include "CUI.h"

#include "CKeyManager.h"
#include "SelectGDI.h"

CUI::CUI()
	: m_pParentUI(nullptr)
	, m_bMouseOn(false)
	, m_bLbtnDown(NULL)
{

}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::Update()
{
	//child ui update
	UpdateChild();
}

void CUI::Finalupdate()
{
	CObject::Finalupdate();

	// UI의 최종 좌표를 구한다.
		m_vFinalPos = GetPos();

	if (GetParent())
	{
		Vector2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	
	// UI Mouse 체크 
	MouseOnCheck();

	FinalupdateChild();
}

void CUI::Render(HDC _dc)
{
	Vector2 vPos = GetFinalPos();
	Vector2 vScale = GetScale();

	if (m_bLbtnDown)
	{

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));

	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

	//child ui render
	RenderChild(_dc);
}

void CUI::UpdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		if (m_vecChildUI[i]->m_bActive) {
			m_vecChildUI[i]->Update();
		}
	}
}

void CUI::FinalupdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		if (m_vecChildUI[i]->m_bActive) {
			m_vecChildUI[i]->Finalupdate();
		}
	}
}

void CUI::RenderChild(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		if (m_vecChildUI[i]->m_bActive)
		{
			m_vecChildUI[i]->Render(_dc);
		}
	}
}

void CUI::MouseOnCheck()
{
	Vector2 vMousePos = CKeyManager::GetInstance()->GetMousePos();
	Vector2 vScale = GetScale();


	if( m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x 
	   && m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnup()
{

}

void CUI::MouseLbtnClicked()
{

}