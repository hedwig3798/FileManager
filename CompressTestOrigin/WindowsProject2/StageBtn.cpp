#include "pch.h"
#include "StageBtn.h"
#include "CGameEixt.h"
#include "CObject.h"
#include "CUI.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "CKeyManager.h"
#include "SoundManager.h"

StageBtn::StageBtn(int _i, int _j) :
	i(_i),
	j(_j),
	pStageStage(nullptr)
{
	int stage = i * 4 + j;

	if (stage > 7 && stage <= 13)
	{
		pStageStage = TextureManager::GetInstance()->LoadTexture(L"2", L"texture\\2.bmp");
		stage -= 8;
	}
	else if (stage <= 7)
	{
		pStageStage = TextureManager::GetInstance()->LoadTexture(L"1", L"texture\\1.bmp");
	}
	else if (stage > 13 && stage <= 16)
	{
		pStageStage = TextureManager::GetInstance()->LoadTexture(L"3", L"texture\\3.bmp");
		stage -= 14;
	}

	wstring name = std::to_wstring(i) + std::to_wstring(j);
	pStageBtn = TextureManager::GetInstance()->LoadTexture(L"relicON", L"texture\\relicON.bmp");
	wstring temp = L"texture\\";
	pStageRoom = TextureManager::GetInstance()->LoadTexture(std::to_wstring(stage + 1).c_str(), temp + std::to_wstring(stage + 1) + L".bmp");

	wstring minus1 = std::to_wstring(i) + std::to_wstring(j);
	pMinus = TextureManager::GetInstance()->LoadTexture(L"muse", L"texture\\m.bmp");
}

StageBtn::~StageBtn()
{

}

void StageBtn::MouseOn()
{

}

void StageBtn::MouseLbtnDown()
{
	SoundManager::GetInstance()->Play(SOUND::EFFECT_BUTTON, SOUND_CHANNAL::BGM);
}

void StageBtn::MouseLbtnup()
{
	SoundManager::GetInstance()->Play(SOUND::BACKGROUND_INGAME, SOUND_CHANNAL::BGM);
	ChangeScene(SCENE_TYPE((i * 4 + j) + (int)(SCENE_TYPE::STAGE_1_1)));
}

void StageBtn::Render(HDC _dc)
{
	int iWidth = (int)pStageBtn->Width();
	int iHeight = (int)pStageBtn->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, pStageBtn->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	iWidth = (int)pStageStage->Width();
	iHeight = (int)pStageStage->Height();
	TransparentBlt(_dc
		, (int)(vPos.x) + 70
		, (int)(vPos.y) + 85
		, iWidth / 4, iHeight / 4
		, pStageStage->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	iWidth = (int)pStageRoom->Width();
	iHeight = (int)pStageRoom->Height();
	TransparentBlt(_dc
		, (int)(vPos.x) + 110
		, (int)(vPos.y) + 85
		, iWidth / 4, iHeight / 4
		, pStageRoom->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	iWidth = (int)pMinus->Width();
	iHeight = (int)pMinus->Height();
	TransparentBlt(_dc
		, (int)(vPos.x) + 90
		, (int)(vPos.y) + 85
		, iWidth / 4, iHeight / 4
		, pMinus->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void StageBtn::Update()
{

}
