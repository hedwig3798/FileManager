#include "pch.h"
#include "CThron.h"

CThron::CThron(bool _isPast)
	: m_bIsOn(false)
	, m_bIsPast(_isPast)
{
	m_pTexture = TextureManager::GetInstance()->LoadTexture(L"", L"texture\\thorntrap.bmp");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2(60.f, 60.f));
	GetCollider()->SetScale(Vector2(120.f, 120.f));
	GetCollider()->SetOffsetPos(Vector2(60, 60));
}

CThron::~CThron()
{

}

void CThron::Update()
{
}

void CThron::Render(HDC _dc)
{
	Vector2	vPos = GetPos();
	Vector2 vScale = GetScale();

	int w = m_pTexture->Width();
	int h = m_pTexture->Height();
	int x = 0;
	int y = 0;
	if (m_bIsPast)
	{
		if (!m_bIsOn)
		{
		}
		else
		{
			x += w / 2;
		}
	}
	else
	{
		y += h / 2;
		if (!m_bIsOn)
		{
		}
		else
		{
			x += w / 2;
		}
	}

	TransparentBlt(_dc
		, (int)(vPos.x + vScale.x / 4)
		, (int)(vPos.y + vScale.y / 4)
		, (int)(vScale.x / 2)
		, (int)(vScale.y / 2)
		, m_pTexture->GetDC()
		, x
		, y
		, w / 2
		, h / 2
		, RGB(255, 0, 255));
}

void CThron::OnCollisionEnter(CCollider* _pOther)
{
	//if (_pOther->GetObj()->GetName() == L"Player")
	//{
	//	m_bIsOn = true;
	//}
}

void CThron::OnCollisionExit(CCollider* _pOther)
{
	//if (_pOther->GetObj()->GetName() == L"Player")
	//{
	//	m_bIsOn = false;
	//}
}
