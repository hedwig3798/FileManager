#include "pch.h"
#include "Stage1_4Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

Stage1_4Btn::Stage1_4Btn()
{
	pStage1_4Btn = TextureManager::GetInstance()->LoadTexture(L"1-4", L"texture\\relicON.bmp");
}

Stage1_4Btn::~Stage1_4Btn()
{

}

void Stage1_4Btn::MouseOn()
{

}

void Stage1_4Btn::MouseLbtnDown()
{

}

void Stage1_4Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_2);
}

void Stage1_4Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage1_4Btn->Width();
	int iHeight = (int)pStage1_4Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_4Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_4Btn::Update()
{

}
