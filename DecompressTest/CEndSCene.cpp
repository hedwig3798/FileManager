///endscene 오브젝트를 불러와서 endscene 만든다
#include "pch.h"
#include "CEndSCene.h"
#include "EndSceneObject.h"

class EndSceneObject;

CEndSCene::CEndSCene(HWND hWnd, HDC hDC, POINT screenRes):CScene(hWnd,hDC,screenRes)	
{
}

CEndSCene::~CEndSCene()
{
}

void CEndSCene::Update() 
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
				continue;
			}
			else if (!(*iter)->m_bActive)
			{
				iter++;
			}
			else
			{
				(*iter)->Update();
				iter++;
			}
		}
	}
}

//오브젝트 세팅
///끝이니까 인자는 없어야되는 줄 알았는데 아니다. 무조건 있어야한다
void CEndSCene::Enter(bool _isPast)	
{
	SoundManager::GetInstance()->Play(SOUND::BACKGROUND_ENDING, SOUND_CHANNAL::BGM);

	//엔딩 오브젝트 추가
	EndSceneObject* pEndSceneObject = new EndSceneObject;
	AddObject(pEndSceneObject, GROUP_TYPE::DEFAULT);

}

bool CEndSCene::Exit()
{
	SoundManager::GetInstance()->Stop(BGM);
	//모든 오브젝트 삭제
	DeleteAll();
	return false;	///현재 시점에서 엔딩
}