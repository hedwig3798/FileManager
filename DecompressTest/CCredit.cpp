#include "pch.h"
#include "CCredit.h"
#include "CTimeMgr.h"
CCredit::CCredit(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes), m_fTime(3), m_fCTime(10.0f)
{
	ending = TextureManager::GetInstance()->LoadTexture(L"credit", L"texture\\credit.bmp");
}

CCredit::~CCredit()
{
}

void CCredit::Enter(bool _isPast)
{
	SoundManager::GetInstance()->Play(SOUND_END, EFFECT);
}

bool CCredit::Exit()
{
	SoundManager::GetInstance()->Stop(EFFECT);
	return false;
}

void CCredit::Update()
{
	m_fTime -= CTimeManager::GetInstance()->GetfDT();
	if (m_fTime <= 0)
	{
		m_fCTime -= CTimeManager::GetInstance()->GetfDT();
		if (m_fCTime <= 0)
		{
			ChangeScene(SCENE_TYPE::TITLE);
		}
	}
}

void CCredit::Render(HDC _dc)
{
	if (m_fTime >= 0.0f)
	{
		HBRUSH hollowBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		HBRUSH defaultBrush = (HBRUSH)SelectObject(_dc, hollowBrush);
		Rectangle(_dc, -1, -1, 1921, 1081);
		SelectObject(_dc, defaultBrush);
		DeleteObject(hollowBrush);
	}
	if (m_fTime <= 0.0f)
	{
		HBRUSH hollowBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		HBRUSH defaultBrush = (HBRUSH)SelectObject(_dc, hollowBrush);
		Rectangle(_dc, -1, -1, 1921, 1081);
		SelectObject(_dc, defaultBrush);
		DeleteObject(hollowBrush);
		TransparentBlt(
			_dc,
			1920 / 2 - ending->Width() / 2,
			((ending->Height() + 1080) * (m_fCTime / 10)) - ending->Height(),
			ending->Width(),
			ending->Height(),
			ending->GetDC(),
			0,
			0,
			ending->Width(),
			ending->Height(),
			RGB(255,0,255)
			);
	}
}