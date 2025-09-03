#include "pch.h"
#include "CPanelUI.h"

#include "CKeyManager.h"
#include "TextureManager.h"

CPanelUI::CPanelUI()
{
	pPanelUI = TextureManager::GetInstance()->LoadTexture(L"pPanelUI", L"texture\\PanelUI.bmp");
}

CPanelUI::~CPanelUI()
{

}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		CKeyManager::GetInstance()->GetMousePos() - m_vDragStart;
	}

}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = CKeyManager::GetInstance()->GetMousePos();
}

void CPanelUI::MouseLbtnup()
{

}

void CPanelUI::Render(HDC _dc)
{

	int iWidth = (int)pPanelUI->Width();
	int iHeight = (int)pPanelUI->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x )
		, (int)(vPos.y)
		, iWidth, iHeight
		, pPanelUI->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CPanelUI::Update()
{

}
