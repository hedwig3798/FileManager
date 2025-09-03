#pragma once
#include "CObject.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Animator.h"
class Texture;

class CWhip :
    public CObject
{
private:
    float m_fTheta;
    OBJECT_DIR  m_dir;
    float m_fLifeTiem;

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(OBJECT_DIR _vDir)
    {
        m_dir = _vDir;
    }


public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    // 객체들이 복사 생성자를 호출할 때, 클론 리턴
    virtual CWhip* Clone() { return new CWhip(*this); }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CWhip(bool _isLeft);
    ~CWhip();
};