#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner;			// Collider를 소유하고 있는 오브젝트
	Vector2	m_vOffsetPos;		// 오브젝트로 부터 상대적인 위치
	Vector2	m_vFinalPos;		// finalupdate 에서 매 프레임 마다 계산
	Vector2	m_vScale;			// 충돌체 크기

	UINT	m_iID;				// 충돌체 고유한 ID 값
	UINT	m_iCol;				
	

public:
	void SetOffsetPos(Vector2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }

	Vector2 GetOffsetPos() { return m_vOffsetPos; }
	Vector2 GetScale() { return m_vScale; }
	Vector2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void Finalupdate();
	void Render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther);					// 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);				// 충돌 진입 시
	void OnCollisionExit(CCollider* _pOther);				// 충돌 해제 시


	CCollider& operator=(CCollider& _origin) = delete;		// 해당 오퍼레이트를 삭제

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

