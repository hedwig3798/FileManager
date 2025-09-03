#pragma once
#include "pch.h"
#include "CObject.h"
#include "Texture.h"
#include "TextureManager.h"


class EmptyObject1 :public CObject
{
public:
	
	//그림으로 쓸 텍스쳐
	Texture* m_pTexture[4];
	int m_iIndex;
// 	//애니메이션으로 쓸 텍스쳐
// 	Texture* m_pTextureAnimation;
	
	bool LeverOnOff; //복붙해서 이름 그대로썼다. 다만 충돌때 써야할 변수를 클래스 생성자에서 초기화해야하는걸 표시할 뿐이다, 선언은 헤더파일에, 초기화는 cpp에서



public:
	bool m_bIsOn;
	bool m_bIsPast;


public:
	//빈 오브젝트의 상태
	EMPTYOBJECT_STATE m_EmptyObjCurrentState;

	//상태변화 딜레이 추가해야되나??

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	//필수
	virtual EmptyObject1* Clone() { return new EmptyObject1(*this); }
	//충돌이 구현된다면
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	EmptyObject1();
	~EmptyObject1();

};

