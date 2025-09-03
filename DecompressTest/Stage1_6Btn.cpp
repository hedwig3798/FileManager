#include "pch.h"
#include "Stage1_6Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

Stage1_6Btn::Stage1_6Btn()
{
	pStage1_6Btn = TextureManager::GetInstance()->LoadTexture(L"1-6", L"texture\\relicON.bmp");
}

Stage1_6Btn::~Stage1_6Btn()
{

}

void Stage1_6Btn::MouseOn()
{

}

void Stage1_6Btn::MouseLbtnDown()
{

}

void Stage1_6Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_6);
}

void Stage1_6Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage1_6Btn->Width();
	int iHeight = (int)pStage1_6Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_6Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_6Btn::Update()
{

}
