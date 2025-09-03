///poison 타일 3개 만들기
///3개 중 하나를 랜덤으로 ? 
///CThron 과 비슷하게 만들어라
#include "pch.h"

#include "CPoison.h"
#include "CPoisonTile.h"
#include "TextureManager.h"
#include <random>

///update하지는 않지만, 
void CPoisonTile::Update()
{
}

///애니메이션 만들지 않는다. 그러니 render한다
void CPoisonTile::Render(HDC _dc)
{
	Vector2	vPos = GetPos();
	Vector2 vScale = GetScale();
	int w = pPoisonTexture[m_iIndex]->Width();
	int h = pPoisonTexture[m_iIndex]->Height();
	int x = 0;
	int y = 0;
	TransparentBlt(_dc
		, (int)(vPos.x + vScale.x / 4)
		, (int)(vPos.y + vScale.y / 4)
		, (int)(vScale.x / 2)
		, (int)(vScale.y / 2)
		, pPoisonTexture[m_iIndex]->GetDC()		///생성자에 있는 rand함수에 의해 m_iIndex가 0,1,2중 랜덤으로 정해진다
		, x
		, y
		, w
		, h
		, RGB(255, 0, 255));
}

///생성자
CPoisonTile::CPoisonTile()
	:m_bIsOn(false)
	,m_bIsPast(false)

{
	///정의만 한다. 선언을 헤더파일에 했다. 
	///만약에 중괄호 안에 선언했다면, 여기서만 쓸 수 있는데, 선언을 헤더파일에 했기 때문에 중괄호 부분 끝나도 안없어짐
	pPoisonTexture[0] = TextureManager::GetInstance()->LoadTexture(L"Poision1", L"texture\\poisiontile1.bmp");	//1번

	pPoisonTexture[1] = TextureManager::GetInstance()->LoadTexture(L"Poision2", L"texture\\poisiontile2.bmp");	//2번

	pPoisonTexture[2] = TextureManager::GetInstance()->LoadTexture(L"Poision3", L"texture\\poisiontile3.bmp");	//3번

	///생성자에서 rand함수를 사용, rand함수의 정의는 <random>에 있다
	m_iIndex = rand() % 3;

}


//소멸자
CPoisonTile::~CPoisonTile()
{
}
