#include "pch.h"
#include "Stage1_2Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

Stage1_2Btn::Stage1_2Btn()
{
	pStage1_2Btn = TextureManager::GetInstance()->LoadTexture(L"1-2", L"texture\\relicON.bmp");
}


Stage1_2Btn::~Stage1_2Btn()
{

}

void Stage1_2Btn::MouseOn()
{

}

void Stage1_2Btn::MouseLbtnDown()
{

}

void Stage1_2Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_2);
}

void Stage1_2Btn::Render(HDC _dc)
{
	int iWidth = (int)pStage1_2Btn->Width();
	int iHeight = (int)pStage1_2Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_2Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_2Btn::Update()
{

}
