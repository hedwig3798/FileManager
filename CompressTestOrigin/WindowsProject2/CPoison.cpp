#include "pch.h"
#include "CPoison.h"
#include "TextureManager.h"

CPoison::CPoison()
{
	pPoison = TextureManager::GetInstance()->LoadTexture(L"Poison", L"texture\\iconPoison.bmp");
}

CPoison::~CPoison()
{

}

void CPoison::Render(HDC _dc)
{

	int iWidth = (int)pPoison->Width();
	int iHeight = (int)pPoison->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x + 150.f)
		, (int)(vPos.y + 25.f)
		, iWidth, iHeight
		, pPoison->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

}
