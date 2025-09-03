#pragma once

class CObject;		///Animator를 소유한 오브젝트의 포인터를 쓰기 위해
class Animation;	//애니메이션 만들어야하니까
class Texture;		//텍스쳐 불러와야하니까

class Animator
{
	///Animator 클래스에서 쓸 변수 4개 생성
private:
	map<wstring, Animation*>	m_mapAnimation;			//모든 Animation
	Animation*					m_pCurrentAnimation;	//현재 재생중인 Animation
	
	CObject*					m_pOwner;	//Animator 소유 오브젝트
	/// 컴포넌트는 오브젝트형 포인터를 가지고있다.owner라고 표현한 건.자기 자신(컴포넌트)을 소유하고 있다는 표현이다
	///	컴포넌트가 가져와서 쓸 오브젝트의 주소를 가지고 있다
	
	bool						m_bRepeat;	//반복재생 여부



public:
	///GetObject 함수는와 GetCurrentAnimation 함수는 pOwner와 pCurrentAnimation을 반환
	CObject* GetObj() { return m_pOwner; }	
	

	///const 붙은 위치가..? 물어보자
	Animation* GetCurrentAnimation() const
	{
		return m_pCurrentAnimation;
	}


public:
	void CreateAnimation(const wstring& _strName, Texture* _pTexture, Vector2 _vLT, Vector2 _vSilceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount, float _scale = 1.0f);
	Animation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void Update();
	void Render(HDC _dc);
	void FinalUpdate();
	


public:
	Animator();
	~Animator();

	//컴포넌트이기 때문에 해당 오브젝트에서 private 변수에 접근할 수 있도록 friend class Object로 설정 
	friend class CObject;
};



