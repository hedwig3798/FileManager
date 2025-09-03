#include "pch.h"
#include "Stage1_8Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

Stage1_8Btn::Stage1_8Btn()
{
	pStage1_8Btn = TextureManager::GetInstance()->LoadTexture(L"1-7", L"texture\\relicON.bmp");
}

Stage1_8Btn::~Stage1_8Btn()
{

}

void Stage1_8Btn::MouseOn()
{

}

void Stage1_8Btn::MouseLbtnDown()
{

}

void Stage1_8Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_8);
}

void Stage1_8Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage1_8Btn->Width();
	int iHeight = (int)pStage1_8Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_8Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_8Btn::Update()
{

}
