#include "pch.h"
#include "Stage1_3Btn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"

Stage1_3Btn::Stage1_3Btn()
{
	pStage1_3Btn = TextureManager::GetInstance()->LoadTexture(L"1-3", L"texture\\relicON.bmp");
}

Stage1_3Btn::~Stage1_3Btn()
{

}

void Stage1_3Btn::MouseOn()
{

}

void Stage1_3Btn::MouseLbtnDown()
{

}

void Stage1_3Btn::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::STAGE_1_3);
}

void Stage1_3Btn::Render(HDC _dc)
{
	

	int iWidth = (int)pStage1_3Btn->Width();
	int iHeight = (int)pStage1_3Btn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStage1_3Btn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void Stage1_3Btn::Update()
{

}
