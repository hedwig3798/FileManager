///arrow는 화살 발사장치다
#include "pch.h"
#include "CTrapArrow.h"

//기본 생성자에서 초기화
CTrapArrow::CTrapArrow()	

{
	
}

void CTrapArrow::Update()
{
}

void CTrapArrow::Render(HDC _dc)
{
	


}

void CTrapArrow::CreateMissile()
{
	Vector2 vMissilePos = GetPos();
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vector2(25.f, 25.f));
	pMissile->SetDir(GetDir());
	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}


CTrapArrow::~CTrapArrow()
{
}
