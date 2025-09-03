#pragma once


#include "CObject.h"

class Texture;
class CFire;
class CThron;
class CPoisonTile;

class CTile :
    public CObject
{
private:
    HDC m_hDC;
    Texture* m_pTileTex;
    int         m_iImgIdx;
    int         m_iOldImgIdx;
    bool        m_CheckCollider;
    int         m_TileType;
    int         m_TriggerNumber;
    int         m_TriggerDir;
    CFire* pFire;
    CThron* pThron;
    CPoisonTile* pPoison;

    // 발판 트리거 한번 작동
    bool        m_TriggerOnce;

public:
    void SetTexture(Texture* _pTex) { m_pTileTex = _pTex; }
    void SetImgIdx(int _CopyIdx) { m_iImgIdx = _CopyIdx; }
    void AddImgIdx() { ++m_iImgIdx; }
    void MinusImgIdx() { if (m_iImgIdx > 0) --m_iImgIdx; }
    void AddTileType()
    {
        m_TileType++;
        if (m_TileType >= (int)TILE_TYPE::END)
            m_TileType = (int)TILE_TYPE::MOVABLE;
    }
    void AddTriggerNumber()
    {
        m_TriggerNumber++;
        if (m_TriggerNumber >= 20)
            m_TriggerNumber = 0;
    }
    void AddTriggerDir()
    {
        m_TriggerDir++;
        if (m_TriggerDir > 3)
            m_TriggerDir = 0;
    }

    int GetImgIdx() { return m_iImgIdx; }
    int GetTileType() { return m_TileType; }
    int GetTriggerNumber() { return m_TriggerNumber; }
    CThron* GetThron() { return pThron; }
    CFire* GetFire() { return pFire; }
    OBJECT_DIR GetTriggerDir() { return (OBJECT_DIR)m_TriggerDir; }

public:
    void EditMode(HDC _dc, Vector2 _RenderPos, Vector2 _Scale);
    void CreateFire(GROUP_TYPE _ObjectType);
    void CheckCollider();

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

    void TriggerOn(int _TriggerNumber, GROUP_TYPE _ObjectType);

private:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);
    void CreateBrushPen();
    virtual CObject* Clone() { return new CTile(*this); }
    HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
    HPEN	m_arrPen[(UINT)PEN_TYPE::END];
public:
    CTile(HDC hDC);
    ~CTile();
};