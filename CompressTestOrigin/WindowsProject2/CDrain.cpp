//관상용으로 만든 Drain
#include "pch.h"
#include "CDrain.h"

//랜덤함수 쓰고싶을때
#include <random>

// 애니메이션 만들고 싶을때
// #include "Animator.h"
// #include "Animation.h"


//기본 생성자
///컴포넌트 추가할 곳
//텍스쳐 받는다
//텍스쳐의 초기상태는 생성자에서 정의한다
CDrain::CDrain()
	:m_bIsOn(false)		//오브젝트 꺼진상태
	, m_bIsPast(false)	//현재상태
	, m_iIndex(0)
{
	//애니메이션쓰지 않는 텍스쳐
	//불러올 텍스쳐는 생성자에 정의한다, 선언은 헤더파일에 했다
	m_DrainTexture[0] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject1", L"texture\\Green.bmp");	//1번
	m_DrainTexture[1] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject2", L"texture\\OR.bmp");	//2번
	m_DrainTexture[2] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject3", L"texture\\Red.bmp");	//3번

	///생성자에서 rand함수를 사용, rand함수의 정의는 <random>에 있다
	m_iIndex = rand() % 3;	//배열의 크기 4로 잡았다
}


//업데이트는 무조건 있어야한다
void CDrain::Update()
{

}


//애니메이션 만들기 싫을때는 render
void CDrain::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	int w = m_DrainTexture[m_iIndex]->Width();
	int h = m_DrainTexture[m_iIndex]->Height();
	int x = 0;
	int y = 0;
	TransparentBlt(_dc
		, (int)(vPos.x + vScale.x / 4)
		, (int)(vPos.y + vScale.y / 4)
		, (int)(vScale.x / 2)
		, (int)(vScale.y / 2)
		, m_DrainTexture[m_iIndex]->GetDC()
		, x
		, y
		, w
		, h
		, RGB(255, 0, 255));
}





CDrain::~CDrain()
{
}
