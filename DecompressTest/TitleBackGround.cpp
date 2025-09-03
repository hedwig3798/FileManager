#include "pch.h"
#include "TitleBackGround.h"
#include "Texture.h"
#include "TextureManager.h"

TitleBackGround::TitleBackGround()
{
	pBackGround = TextureManager::GetInstance()->LoadTexture(L"BackGround", L"texture\\title_01.bmp");
}

TitleBackGround::~TitleBackGround()
{

}

void TitleBackGround::Update()
{

}

void TitleBackGround::Render(HDC _dc)
{
	int width = pBackGround->Width();
	int height = pBackGround->Height();

	TransparentBlt(_dc, 0, 0, width, height, pBackGround->GetDC(), 0, 0, width, height, RGB(255,0,255));
}

