#include "pch.h"
#include "CClock.h"
#include "TextureManager.h"

CClock::CClock()
{
	
	pClock = TextureManager::GetInstance()->LoadTexture(L"clock", L"texture\\iconDead.bmp");
}

CClock::~CClock()
{
}

void CClock::Render(HDC _dc)
{

	int iWidth = (int)pClock->Width();
	int iHeight = (int)pClock->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x +150.f)
		, (int)(vPos.y + 25.f)
		, iWidth, iHeight
		, pClock->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

}
