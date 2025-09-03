///밟으면 들어가는 버튼 만들기
#include "pch.h"
#include "CFootButton.h"
//관상용으로 쓸 빈 오브젝트
//텍스쳐 받아서 따로 넣어줄것임, 기본은 텍스쳐 받아서 정지상태


//기본 생성자
///컴포넌트 추가할 곳
//텍스쳐 받는다
//텍스쳐의 초기상태는 생성자에서 정의한다
CFootButton::CFootButton(bool _isPast)
	:m_bIsPast(_isPast)	//0:현재, 1:과거
	, m_bIsOn(false)		//0:안밟았다, 1:밟았다 
	, m_iIndex(0)
{
	//애니메이션쓰지 않는 텍스쳐
	//불러올 텍스쳐는 생성자에 정의한다, 선언은 헤더파일에 했다
	m_pTexture = TextureManager::GetInstance()->LoadTexture(L"CurrentFootButtonOFF", L"texture\\foothold.bmp");	//1번 (현재, 안밟)	 (0, 0)
	CreateCollider();
	GetCollider()->SetScale(Vector2{100, 100});
	GetCollider()->SetOffsetPos(Vector2{ 60, 60 });
}


//업데이트는 무조건 있어야한다
void CFootButton::Update()
{
}


//애니메이션 만들기 싫을때는 render
void CFootButton::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	int w = m_pTexture->Width();
	int h = m_pTexture->Height();

	int x = 0;
	int y = 0;

	//상태에 따라 4개가 필요하다
	///단, x,y중 그대로 0인 것은 쓰지 않아도 된다
	if ((m_bIsOn == false) && (m_bIsPast == false))	//(현재, 안밟)	(0, 0)
	{
	}
	else if ((m_bIsOn == true) && (m_bIsPast == false))	//2번 (현재, 밟)	(0, 1)
	{
		x = w / 2;
	}
	else if ((m_bIsOn == false) && (m_bIsPast == true))	//3번 (과거, 안밟) (1, 0) 
	{
		y = h / 2;
	}

	else if ((m_bIsOn == true) && (m_bIsPast == true))	//4번 (과거, 밟) ( 1, 1)
	{
		x = w / 2;
		y = h / 2;
	}

	TransparentBlt(_dc
		, (int)(vPos.x + vScale.x / 4)
		, (int)(vPos.y + vScale.y / 4)
		, (int)(vScale.x / 2)
		, (int)(vScale.y / 2)
		, m_pTexture->GetDC()
		, x
		, y
		, w/2
		, h/2
		, RGB(255, 0, 255));
}


///충돌체크하고, 그 안에 if문 옮겨
///충돌 하면 m_bIsOn==true, 그상태가 유지되다가
///다시 밟으면 m_bIsOn==false, 되고 그 상태가 유지된다
///위의 과정이 반복된다

//충돌함수 만든다 CLever.cpp 참고했는데, 가만히 있는데 플레이어가 와서 발생하는 충돌이다. (플레이어가 이동해서 발생하는 충돌과 구분해야함)
void CFootButton::OnCollisionEnter(CCollider* _pOther)
{
	///발판을 밟는다고 과거,현재가 바뀌지 않는다. 과거, 현재는 CLever에서 구현되었다
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		m_bIsOn = true;	//밟
	}
}

CFootButton::~CFootButton()
{


}


