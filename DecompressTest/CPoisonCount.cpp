#include "pch.h"
#include "CPoisonCount.h"
#include "Texture.h"
#include "TextureManager.h"
#include "CPathManager.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CCollisionManager.h"
class CScene;


CPoisonCount::CPoisonCount()
	:m_iPosionCount(0)
{
	//임시 리소스 파일로 체크하기 (이현장)
	pPoisonCount = TextureManager::GetInstance()->LoadTexture(L"w0", L"texture\\w0.bmp");
	pPoisonCount1 = TextureManager::GetInstance()->LoadTexture(L"w1", L"texture\\w1.bmp");
	pPoisonCount2 = TextureManager::GetInstance()->LoadTexture(L"w2", L"texture\\w2.bmp");
	pPoisonCount3 = TextureManager::GetInstance()->LoadTexture(L"w3", L"texture\\w3.bmp");
	// tmep의 활용 법 (이현장)
	pNowPoisonCount = pPoisonCount;
}

CPoisonCount::~CPoisonCount()
{

}

void CPoisonCount::Update()
{	
	//아래있는 것을 활용해서 해야할것들 (이현장)
	vector<CObject*> objVector = CSceneManager::GetInstance()->GetCurScene()->GetGroupObject(GROUP_TYPE::PLAYER);
	if (objVector.size() == 0 || objVector[0] == NULL)
	{
		return;
	}
	// 동적 형변환
	CPlayer* player = dynamic_cast<CPlayer*>(objVector[0]);
	m_iPosionCount = player->m_iPoision;
}

void CPoisonCount::Render(HDC _dc)
{


	switch (m_iPosionCount)
	{
	case 0:
		pNowPoisonCount = pPoisonCount;
		break;
	case 1:
		pNowPoisonCount = pPoisonCount1;
		break;
	case 2:
		pNowPoisonCount = pPoisonCount2;
		break;
	case 3:
		pNowPoisonCount = pPoisonCount3;
		break;
	default:
		break;
	}


	int iWidth = (int)pNowPoisonCount->Width();
	int iHeight = (int)pNowPoisonCount->Height();
	Vector2 vPos = GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x )
		, (int)(vPos.y )
		, iWidth, iHeight
		, pNowPoisonCount->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
	//ComponentRender(_dc);
}
