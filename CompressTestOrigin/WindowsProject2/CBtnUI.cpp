#include "pch.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "TextureManager.h"

CBtnUI::CBtnUI()
{
	pBtnUI = TextureManager::GetInstance()->LoadTexture(L"pBtnUI", L"texture\\uititle.bmp");
}

CBtnUI::~CBtnUI()
{

}

void CBtnUI::MouseOn()
{

}

void CBtnUI::MouseLbtnDown()
{

}

void CBtnUI::MouseLbtnup()
{

}

void CBtnUI::Render(HDC _dc)
{
	int iWidth = (int)pBtnUI->Width();
	int iHeight = (int)pBtnUI->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pBtnUI->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CBtnUI::Update()
{
	
}
