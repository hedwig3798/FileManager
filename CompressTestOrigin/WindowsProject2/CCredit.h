#pragma once
#include "CScene.h"
#include "Texture.h"
#include "TextureManager.h"
class CCredit :
    public CScene
{
public:
    virtual void Enter(bool _isPast);
    virtual bool Exit();
    virtual void Update();
    virtual void Render(HDC _dc);

    CCredit(HWND hWnd, HDC hDC, POINT screenRes);
    ~CCredit();

    float m_fTime;
    float m_fCTime;

    Texture* ending;
};

