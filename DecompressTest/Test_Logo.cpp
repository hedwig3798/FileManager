#include "pch.h"
#include "Test_Logo.h"
#include "TextureManager.h"

Test_Logo::Test_Logo()
{
	pTextLogo = TextureManager::GetInstance()->LoadTexture(L"UI1", L"texture\\mainruins_try.bmp");
}

Test_Logo::~Test_Logo()
{

}

void Test_Logo::Update()
{

}

void Test_Logo::Render(HDC _dc)
{
	int iWidth = (int)pTextLogo->Width();
	int iHeight = (int)pTextLogo->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x + 70.f)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pTextLogo->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}
