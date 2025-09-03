#pragma once
#include "CObject.h"
#include "Texture.h"
#include "TextureManager.h"
#include "CCollider.h"

class CCollider;
class Texture;

class CThron :
    public CObject
{
public:
    CThron(bool _isPast);
    ~CThron();

    void Update() override;
    void Render(HDC _dc) override;
    virtual CThron* Clone() { return (CThron*)this; }
    void IsOn()
    {
        m_bIsOn = true;
    }
    void SetIsOn(bool _setbool)
    {
        if (m_bIsOn)
            m_bIsOn = false;
        else
            m_bIsOn = true;
    }
    bool GetIsOn() { return m_bIsOn; }

    ///virtual 쓰면 자식에게 그 함수를 상속한다(자식클래스에서 재정의 할 수 있다)
    ///virtual이 없으면, 그 함수를 자식에게 상속하지 않는다
    ///override가 붙어있으면, 부모클래스의 그 함수에 virtual이 붙어있다는 뜻
   
    ///여기엔 virtual 안붙었다. 이말은, CThron클래스가 자식클래스를 가지더라도 자식클래스에서 OnCollisionEnter함수를 재정의 하지 않는다는 뜻이다
    ///하지만, 뒤에 override 붙어있으니까, CThron클래스의 부모클래스인 CObject클래스의 OnCollisionEnter함수는 virtual이 붙었음을 알 수 있다
    void OnCollisionEnter(CCollider* _pOther) override;
    void OnCollisionExit(CCollider* _pOther) override;

    bool m_bIsPast;
private:
    Texture* m_pTexture;

    bool m_bIsOn;
};

