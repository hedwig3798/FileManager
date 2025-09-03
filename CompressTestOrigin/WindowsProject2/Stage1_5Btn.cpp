#include "pch.h"
#include "Stage1_5Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"


Stage1_5Btn::Stage1_5Btn()
{
	pStage1_5Btn = TextureManager::GetInstance()->LoadTexture(L"1-5", L"texture\\relicON.bmp");
}

Stage1_5Btn::~Stage1_5Btn()
{
	
}

void Stage1_5Btn::MouseOn()
{

}

void Stage1_5Btn::MouseLbtnDown()
{

}

void Stage1_5Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_5);
}

void Stage1_5Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage1_5Btn->Width();
	int iHeight = (int)pStage1_5Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_5Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_5Btn::Update()
{

}
