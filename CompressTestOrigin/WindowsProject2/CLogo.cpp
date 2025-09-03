#include "pch.h"
#include "CLogo.h"
#include "Texture.h"
#include "TextureManager.h"

CLogo::CLogo()
{
	pLogo = TextureManager::GetInstance()->LoadTexture(L"Logo", L"texture\\titlerogo.bmp");
}
CLogo::~CLogo()
{

}

void CLogo::Render(HDC _dc)
{
 	int iWidth = (int)pLogo->Width();
 	int iHeight = (int)pLogo->Height();
 	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x - 100)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pLogo->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CLogo::Update()
{

}

