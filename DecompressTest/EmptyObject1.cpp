//관상용으로 쓸 빈 오브젝트
//텍스쳐 받아서 따로 넣어줄것임, 기본은 텍스쳐 받아서 정지상태
#include "pch.h"
#include "EmptyObject1.h"

//랜덤함수 쓰고싶을때
//#include <random>


// 애니메이션 만들고 싶을때 (CLever.cpp 참고)
// #include "Animator.h"
// #include "Animation.h"

//충돌구현
#include "CCollider.h"




//기본 생성자
///컴포넌트 추가할 곳
//텍스쳐 받는다
//텍스쳐의 초기상태는 생성자에서 정의한다
EmptyObject1::EmptyObject1()
	:m_bIsOn(false)		//오브젝트 꺼진상태
	, m_bIsPast(false)	//현재상태
	, m_EmptyObjCurrentState(EMPTYOBJECT_STATE::DEFAULT1)
	, m_iIndex(0)

	,LeverOnOff(false)	//복붙해서 이름 그대로썼다. 다만 충돌때 써야할 변수를 클래스 생성자에서 초기화해야하는걸 표시할 뿐이다, 선언은 헤더파일에, 초기화는 cpp에서

{
	//애니메이션쓰지 않는 텍스쳐
	//불러올 텍스쳐는 생성자에 정의한다, 선언은 헤더파일에 했다
	m_pTexture[0] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject1", L"texture\\Green.bmp");	//1번
	m_pTexture[1] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject2", L"texture\\OR.bmp");	//2번
	m_pTexture[2] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject3", L"texture\\Red.bmp");	//3번
	m_pTexture[3] = TextureManager::GetInstance()->LoadTexture(L"EmptyObject4", L"texture\\wh.bmp");	//4번

	///생성자에서 rand함수를 사용, rand함수의 정의는 <random>에 있다
	//m_iIndex = rand() % 4;	//배열의 크기 4로 잡았다

	///------------------------------------------------------------
	
	
// 	
// 	//애니메이션으로 쓸 텍스쳐(기본: 플레이어)
// 	Texture* m_pTextureAnimation = TextureManager::GetInstance()->LoadTexture(L"DEFAULT", L"texture\\player_IDLE_Right.bmp");
// 
// 	//애니메이션으로 만들고 싶을때(오브젝트 생성과 동시에 애니메이션이 시작되어야하므로 생성자에 만들어야함)
// 	//애니메이션 세팅하기
// 	CreateAnimator();
// 	//DEFAULT상태 애니메이션
// 	// 전체 68x142 / 가장공간차지하는 캐릭터 60x136	(기본: 플레이어)
// 	GetAnimator()->CreateAnimation(L"DEFAULT",m_pTextureAnimation, Vector2(0.f, 0.f), Vector2(68.0f, 142.f), Vector2(68.f, 0.f), 0.3f, 2);
// 	if (m_bIsPast)
// 	{
// 		GetAnimator()->Play(L"DEFAULT");
// 	else
// 	{
// 	}
// 		GetAnimator()->Play(L"Prev_Lever_Off");
// 	}
}


//업데이트는 무조건 있어야한다
void EmptyObject1::Update()
{

}


//애니메이션 만들기 싫을때는 render
void EmptyObject1::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	int w = m_pTexture[m_iIndex]->Width();
	int h = m_pTexture[m_iIndex]->Height();
	int x = 0;
	int y = 0;
	TransparentBlt(_dc
		, (int)(vPos.x + vScale.x / 4)
		, (int)(vPos.y + vScale.y / 4)
		, (int)(vScale.x / 2)
		, (int)(vScale.y / 2)
		, m_pTexture[m_iIndex]->GetDC()
		, x
		, y
		, w
		, h
		, RGB(255, 0, 255));
}


// 충돌함수 만든다 CLever.cpp 참고했는데, 가만히 있는데 플레이어가 와서 발생하는 충돌이다. (플레이어가 이동해서 발생하는 충돌과 구분해야함)
// void EmptyObject1::OnCollisionEnter(CCollider* _pOther)
// {
// 	if (_pOther->GetObj()->GetName() == L"Whip_Player")
// 	{
// 		LeverTriggerOn(this);	///this에서 오류인 이유
// 
// 		if (LeverOnOff)				//LeverOnOff(false복붙해서 이름 그대로썼다. 다만 충돌때 써야할 변수를 클래스 생성자에서 초기화해야하는걸 표시할 뿐이다
// 			LeverOnOff = false;
// 		else
// 			LeverOnOff = true;
// 	}
// }



EmptyObject1::~EmptyObject1()
{
}
