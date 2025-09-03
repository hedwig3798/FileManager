#include "pch.h"
#include "Stage2_1Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"


Stage2_1Btn::Stage2_1Btn()
{
	pStage2_1Btn = TextureManager::GetInstance()->LoadTexture(L"1-7", L"texture\\relicON.bmp");
}

Stage2_1Btn::~Stage2_1Btn()
{

}

void Stage2_1Btn::MouseOn()
{

}

void Stage2_1Btn::MouseLbtnDown()
{

}

void Stage2_1Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_2_1);
}

void Stage2_1Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage2_1Btn->Width();
	int iHeight = (int)pStage2_1Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage2_1Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage2_1Btn::Update()
{

}
