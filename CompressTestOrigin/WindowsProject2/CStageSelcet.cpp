#include "pch.h"
#include "CStageSelcet.h"
#include "TextureManager.h"
CStageSelcet::CStageSelcet()
	: m_iMousecheck(0)
{
	StageSelcet = TextureManager::GetInstance()->LoadTexture(L"StageSelcet", L"texture\\stage_select_up.bmp"); 
	StageSelcetOn = TextureManager::GetInstance()->LoadTexture(L"StageSelcet1", L"texture\\stage_select_down.bmp");
	
	NowStageSelcet = StageSelcet;
}

CStageSelcet::~CStageSelcet()
{

}

void CStageSelcet::MouseOn()
{

}

void CStageSelcet::MouseLbtnDown()
{

}

void CStageSelcet::MouseLbtnup()
{
	ChangeScene(SCENE_TYPE::SELCETMAP);
}

void CStageSelcet::Render(HDC _dc)
{
	switch (m_iMousecheck)
	{
	case 0:
		NowStageSelcet = StageSelcet;
		break;
	case 1:
		NowStageSelcet = StageSelcetOn;
		break;
	default:
		break;
	}
 	int iWidth = (int)NowStageSelcet->Width();
 	int iHeight = (int)NowStageSelcet->Height();
 	Vector2 vPos = GetPos();
 	TransparentBlt(_dc
 		, (int)(vPos.x)
 		, (int)(vPos.y)
 		, iWidth, iHeight
 		, NowStageSelcet->GetDC()
 		, 0, 0, iWidth, iHeight
 		, RGB(255, 0, 255));
}

void CStageSelcet::Update()
{
	if (IsMouseOn())
	{
		m_iMousecheck = 0;
	}
	else
	{
		m_iMousecheck = 1;
	}
}
