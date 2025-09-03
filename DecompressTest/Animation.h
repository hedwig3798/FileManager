////기능은 그대로, 과정은 모두 바꾼다
#pragma once
class Animator;
class Texture;

struct tAnimFrm		///tAnimFrm 은 애니메이션 프레임 구조체
{
	Vector2 vLeftTop;	//좌상단 좌표
	Vector2	vSilce;		///자르려는 애니메이션 1프레임(장면하나) 크기
	Vector2 vOffset;	///두 프레임 시작점의 간격= 두 프레임의 좌상단 x좌표 차이
	float fDuration;	//다음 프레임으로 넘어가는 시간(초 단위)
};


class Animation
{
private:
	wstring				m_strName;
	Animator* m_pAnimator;
	Texture* m_pTexture;			//Animation이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vectorFrame;		//모든 프레임 정보
	int					m_iCurrentFrame;	//현재 프레임
	float				m_fAccountTime;		//시간 누적
	float				m_fScale;

	bool				m_bFinish;			//재생 끝에 도달여부

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	
	void SetFrame(int _iFrameIdx)	///다시 처음 프레임으로 돌아가게 하는 함수
	{
		m_bFinish = false;	//
		m_iCurrentFrame = _iFrameIdx;	//
		m_fAccountTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vectorFrame[_iIdx - 1]; }
	int GetMaxFrame() { return (int)m_vectorFrame.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void Update();
	void Render(HDC _dc);
	void FinalUpdate();
	void Create(Texture* _pTexture, Vector2 _vLeftTop, Vector2 _vSilceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount, float _fScale = 1.0f);
	


public:
	Animation();
	~Animation();

	friend class Animator;		///Animator가 Animation을 관리한다
};

