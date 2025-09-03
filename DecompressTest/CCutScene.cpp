///컷신 오브젝트를 불러와서 컷신을 만든다
#include "pch.h"
#include "CCutScene.h"
#include "CutSceneObject.h"

class CutSceneObject;

CCutScene::CCutScene(HWND hWnd, HDC hDC, POINT screenRes) : CScene(hWnd, hDC, screenRes)	///cpp파일, h파일 CCutScene쓸때 인자도 개수, 종류 똑같이 
{
	m_eNextScene = SCENE_TYPE::STAGE_1_1;
}

CCutScene::~CCutScene()
{

}

void CCutScene::Update() 
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
void CCutScene::Enter(bool _isPast)
{
	//컷신 오브젝트 추가
	CutSceneObject* pCutSceneObject = new CutSceneObject;
	AddObject(pCutSceneObject, GROUP_TYPE::DEFAULT);
}

bool CCutScene::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();
	return false;	///현재에서 시작할거니까 false로 고친다.
}

