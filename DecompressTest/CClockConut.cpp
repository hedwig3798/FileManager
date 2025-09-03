#include "pch.h"
#include "CClockConut.h"
#include "TextureManager.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "CScene.h"

class CScene;

int CPlayer::m_siDeathCount;

CClockConut::CClockConut()
	: m_iClockConut(0),
	m_iClockconutTen(0),
	m_PlayDead(0)
{

	pClockConut[0] = TextureManager::GetInstance()->LoadTexture(L"Clock0", L"texture\\w0.bmp");
	pClockConut[1] = TextureManager::GetInstance()->LoadTexture(L"Clock1", L"texture\\w1.bmp");
	pClockConut[2] = TextureManager::GetInstance()->LoadTexture(L"Clock2", L"texture\\w2.bmp");
	pClockConut[3] = TextureManager::GetInstance()->LoadTexture(L"Clock3", L"texture\\w3.bmp");
	pClockConut[4] = TextureManager::GetInstance()->LoadTexture(L"Clock4", L"texture\\w4.bmp");
	pClockConut[5] = TextureManager::GetInstance()->LoadTexture(L"Clock5", L"texture\\w5.bmp");
	pClockConut[6] = TextureManager::GetInstance()->LoadTexture(L"Clock6", L"texture\\w6.bmp");
	pClockConut[7] = TextureManager::GetInstance()->LoadTexture(L"Clock7", L"texture\\w7.bmp");
	pClockConut[8] = TextureManager::GetInstance()->LoadTexture(L"Clock8", L"texture\\w8.bmp");
	pClockConut[9] = TextureManager::GetInstance()->LoadTexture(L"Clock9", L"texture\\w9.bmp");

	pNowClockCount = pClockConut[0];
}

CClockConut::~CClockConut()
{

}

void CClockConut::Render(HDC _dc)
{
	for (size_t i = 0; i < m_szStringDeatchCount.size(); i++)
	{
		pNowClockCount = pClockConut[m_szStringDeatchCount[(int)i] - '0'];
		int iWidth = (int)pNowClockCount->Width();
		int iHeight = (int)pNowClockCount->Height();
		Vector2 vPos = GetPos();
		TransparentBlt(_dc
			, (int)(vPos.x) + (70 * (int)i)
			, (int)(vPos.y)
			, iWidth, iHeight
			, pNowClockCount->GetDC()
			, 0, 0, iWidth, iHeight
			, RGB(255, 0, 255));
	}

}

void CClockConut::Update()
{
	m_szStringDeatchCount = std::to_string(CPlayer::m_siDeathCount);
}
