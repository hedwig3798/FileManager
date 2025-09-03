#pragma once
class CCollider;
class Animator;

class CObject
{
public:
	virtual void Update() = 0;
	virtual void Finalupdate();
	virtual void Render(HDC _dc);

	void ComponentRender(HDC _dc, bool _CollisionOn);

	// 오브젝트 복사할 때 필요한 함수 ( 순수 가상 함수, 자식 클래스에서 구현 필요 )
	virtual CObject* Clone() = 0;

public:
	// 위치, 크기 세팅
	virtual void SetPos(Vector2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
	Vector2 GetPos() { return m_vPos; }
	Vector2 GetScale() { return m_vScale; }

	// 이름 세팅 후에 콜리전끼리 충돌 처리가 되었을 때, 상대 오브젝트의 이름을 확인하고 예외처리를 할 수 있다.
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	// 컴포넌트 가져오기
	CCollider* GetCollider() { return m_pCollider; }
	Animator* GetAnimator() { return m_pAnimator; }

	// 죽을 오브젝트인지 확인하기 위한 함수
	bool IsDead() { return !m_bAlibe; }

public:
	// 컴포넌트 생성
	void CreateCollider();
	void CreateAnimator();

	// 콜리전 이벤트 발생
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	// 다음 프레임에 죽을 오브젝트 세팅
	void SetDead() { m_bAlibe = false; }

public:
	CObject();									// 기본 생성자
	CObject(const CObject& _origin);			// 복사 생성자
	virtual ~CObject();	// 소멸자	
	bool		m_bActive;
	bool		m_CollisionOn;

private:
	Vector2		m_vPos;			// 위치
	Vector2		m_vScale;		// 크기
	wstring		m_strName;		// 객체 이름
	bool		m_bAlibe;		// 객체 상태
	

	// Component
	CCollider*	m_pCollider;
	Animator*	m_pAnimator;


	friend class CEventMgr;
};
