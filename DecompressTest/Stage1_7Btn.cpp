#include "pch.h"
#include "Stage1_7Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

Stage1_7Btn::Stage1_7Btn()
{
	pStage1_7Btn = TextureManager::GetInstance()->LoadTexture(L"1-7", L"texture\\relicON.bmp");
}


Stage1_7Btn::~Stage1_7Btn()
{

}

void Stage1_7Btn::MouseOn()
{

}

void Stage1_7Btn::MouseLbtnDown()
{

}

void Stage1_7Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_7);
}

void Stage1_7Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage1_7Btn->Width();
	int iHeight = (int)pStage1_7Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_7Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_7Btn::Update()
{

}
