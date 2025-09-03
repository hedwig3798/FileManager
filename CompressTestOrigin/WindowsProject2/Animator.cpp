////기능은 그대로, 과정은 모두 바꾼다
#include "pch.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator()
	:m_pOwner(nullptr)	//Animation 소유한 오브젝트의 주소
	, m_pCurrentAnimation(nullptr)	//현재 재생중인 Animaion의 주소?
	, m_bRepeat(false)	//처음에는 반복재생 안한다. 동작이 끝나면 true로 바뀌어 반복재생
	
{
}

Animator::~Animator()
{
	Safe_Delete_map(m_mapAnimation);	//무슨뜻이더라
}

///scale이 추가되었다. 
						///1.0f는 디폴트값
						///m_fScale은 윈도우 창의 크기를 늘리거나(곱한다), 줄이는데(나눈다), 이 값을 Animator로부터 받아온다
						///Animator는 이 값을 Object로부터 받아온다

///애니메이션 생성: texture를 가져온 다음에 만든다
///그래서  CreateAnimation인자값에 texture포인터형 변수 _pTexture가 있는거다
void Animator::CreateAnimation(const wstring& _strName, Texture* _pTexture, Vector2 _vLeftTop, Vector2 _vSilceSize, Vector2 _vStep
	, float _fDuration, UINT _iFrameCount, float _scale )
{
	//같은 이름을 사용하는 애니메이션이 있는지 체크(FindAnimation 함수 사용)
	//같은 이름을 사용하는 애니메이션이 있을 경우 assert에서 오류 체크
	Animation* pAnimation = FindAnimation(_strName);
	assert(nullptr == pAnimation);	/// pAnimation==nullptr은 안되나?
	///애니메이션 생성할 때 같은 이름을 사용하는 애니메이션 있는지 체크하는 과정, 같은 이름의 애니메이션 찾는 과정은 texture때와 똑같다
	///다만, texture때와 다르게 애니메이션이 없어야 다음 단계로 넘어갈 수 있다

	//애니메이션 객체를 생성 후 이름, 컴포넌트 소유 객체, m_mapAnimation에 이름에 따라 관리해주기 위한 애니메이션을 map에 등록
	pAnimation = new Animation;
	pAnimation->SetName(_strName);	///SetName은 Animaion클래스에 정의되어있음
	pAnimation->m_pAnimator = this;		///m_pAnimator는 Animation 클래스에 정의됨 

	m_mapAnimation.insert(make_pair(_strName, pAnimation));


	//애니메이션 정보를 가지고 생성, create함수에 있는 pTexture는 애니메이션에 사용하는 texture이다
	pAnimation->Create(_pTexture, _vLeftTop, _vSilceSize, _vStep, _fDuration, _iFrameCount, _scale);
}


//똑같은 이름의 애니메이션 찾는 함수
Animation* Animator::FindAnimation(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter;
	iter = m_mapAnimation.find(_strName);
	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

///만들었으면 재생한다
//현재 재생중인 애니메이션 Update()
void Animator::Update()
{
			
}

//현재 재생중인 애니메이션 render
void Animator::Render(HDC _dc)
{
	if (nullptr != GetCurrentAnimation())
	{
		GetCurrentAnimation()->Render(_dc);
	}
}


void Animator::FinalUpdate()
{
	if (nullptr != GetCurrentAnimation())
	{
		GetCurrentAnimation()->FinalUpdate();


		// 애니메이션의 반복 여부를 체크한 bRepeat가 true이고 Animation 객체에서 애니메이션의 마지막을 체크하는 finish의 상태를 가져와서
		// Animation의 프레임을 0으로 세팅하고 finish 변수를 false로 세팅
		if (m_bRepeat && GetCurrentAnimation()->IsFinish())
		{
			GetCurrentAnimation()->SetFrame(0);
		}
	}
}

//인자로 받은 이름의 애니메이션 재생
void Animator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurrentAnimation = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
	m_pCurrentAnimation->m_bFinish = false;
}