////기능은 그대로, 과정은 모두 바꾼다

#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include "Animator.h"
#include "CObject.h"
#include "CTimeMgr.h"

Animation::Animation()
	:m_pAnimator(nullptr)
	, m_pTexture(nullptr)
	, m_iCurrentFrame(0)
	, m_fAccountTime(0.f)
	, m_bFinish(false)
	, m_fScale(1.0f)		///1.0f는 디폴트값
	///m_fScale은 윈도우 창의 크기를 늘리거나(곱한다), 줄이는데(나눈다), 
	/// Animation는 이 값을 Animator로부터 받아온다
{
}

Animation::~Animation()
{
}

void Animation::Update()
{

}

void Animation::Render(HDC _dc)
{
	if (m_bFinish)
		return;
	if (m_fScale <= 0)
	{
		return;
	}
	CObject* pObject = m_pAnimator->GetObj();
	Vector2 vPos = pObject->GetPos();

	vPos += m_vectorFrame[m_iCurrentFrame].vOffset;	// Object Position에 Offset만큼 추가 이동위치

	
	///m_fScale은 윈도우 창의 크기를 늘리거나(곱한다), 줄이는데(나눈다), 
	///Animation은 이 값을 Animator로부터 받아온다
	TransparentBlt(		
		_dc																				///윈도우 창	
		, (int)(vPos.x - m_vectorFrame[m_iCurrentFrame].vSilce.x / (2.f * m_fScale))	 
		, (int)(vPos.y - m_vectorFrame[m_iCurrentFrame].vSilce.y / (2.f * m_fScale))	 
		, (int)(m_vectorFrame[m_iCurrentFrame].vSilce.x / m_fScale)						 
		, (int)(m_vectorFrame[m_iCurrentFrame].vSilce.y / m_fScale)						//object -> animator -> animation 으로 fScale 값이 전달된다
		, m_pTexture->GetDC()															///가져온 텍스쳐 이미지 좌표 및 크기, m_pTexture->GetDC()	: 가져온 텍스쳐 이미지 좌표 및 크기
		, (int)(m_vectorFrame[m_iCurrentFrame].vLeftTop.x)
		, (int)(m_vectorFrame[m_iCurrentFrame].vLeftTop.y)
		, (int)(m_vectorFrame[m_iCurrentFrame].vSilce.x)
		, (int)(m_vectorFrame[m_iCurrentFrame].vSilce.y)
		, RGB(255, 0, 255));															///투명으로 처리할 원본 비트맵의 RGB 색입니다. Magenta 쓰기로 했어

	//가져온 텍스쳐 이미지를 윈도우 창에 그린다고 생각하고 넘어가자
	///fScale은 가져온 텍스쳐를 그릴 위치(윈도우 창) 에만 적용하고, 가져온 텍스쳐에는 적용하지않는다(만든 게 아니라, 가져온 거니까 그런거다)

}

void Animation::FinalUpdate()
{
	if (m_bFinish)
		return;

	m_fAccountTime += CTimeManager::GetInstance()->GetfDT();

	if (m_fAccountTime > m_vectorFrame[m_iCurrentFrame].fDuration)
	{
		m_iCurrentFrame++;

		if (m_vectorFrame.size() <= m_iCurrentFrame)
		{
			m_iCurrentFrame = 0;
			m_bFinish = true;
			m_fAccountTime = 0.f;
			return;
		}

		m_fAccountTime = m_fAccountTime - m_vectorFrame[m_iCurrentFrame-1].fDuration;
	}
}

void Animation::Create(Texture* _pTexture, Vector2 _vLeftTop, Vector2 _vSilceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount, float _fScale)
{
	m_pTexture = _pTexture;
	m_fScale = _fScale;				///Animation 클래스의 멤버변수에 create함수의 인자를 대입하는 방법: this 포인터 이용한다
									///클래스의 멤버함수는, this라는 매개변수가 암시적으로 포함되어있다. this는 포인터(자기 자신의 객체를 가리키는 포인터)이다  

	tAnimFrm AnimationFrame = {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		AnimationFrame.fDuration = _fDuration;
		AnimationFrame.vSilce = _vSilceSize;
		AnimationFrame.vLeftTop = _vLeftTop + _vStep * i;

		//정보 다 입력하고 vector배열에 입력
		m_vectorFrame.push_back(AnimationFrame);
	}
}