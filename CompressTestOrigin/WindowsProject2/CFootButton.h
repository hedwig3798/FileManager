///밟으면 들어가는 버튼 만들기

#pragma once
#include "pch.h"
#include "CObject.h"
#include "Texture.h"
#include "TextureManager.h"

#include "CCollider.h" ///충돌체크

class CCollider;
class Texture;

class CFootButton :public CObject
{
public:
	CFootButton(bool _isPast);
	~CFootButton();

	//그림으로 쓸 텍스쳐 4장 필요하다
	Texture* m_pTexture;
	int m_iIndex;
	// 	//애니메이션으로 쓸 텍스쳐
	// 	Texture* m_pTextureAnimation;


	bool m_bIsOn;	//밟았니 안밟았니
	bool m_bIsPast;

	

	//빈 오브젝트의 상태
	//FOOTBUTTON_STATE m_FootButtonState;

	//상태변화 딜레이 추가해야되나??


	virtual void Update();
	virtual void Render(HDC _dc);
	virtual CFootButton* Clone() { return new CFootButton(*this); }

	void IsOn()
	{
		m_bIsOn = true;	//밟았다
	}
	void SetIsOn(bool _setbool)
	{
		if (m_bIsOn)
			m_bIsOn = false;
		else
			m_bIsOn = true;
	}
	bool GetIsOn() { return m_bIsOn; }
	void OnCollisionEnter(CCollider* _pOther) /*override*/;		///override가 있고 없고는 무슨 차이?, 재정의라는것만 알고 있음
};

