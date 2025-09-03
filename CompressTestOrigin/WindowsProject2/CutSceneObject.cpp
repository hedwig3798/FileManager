///컷신에 쓸 오브젝트를 만든다
#include "pch.h"
#include "CutSceneObject.h"

//#include "CScene.h"
//#include "CScene_Title.h"
#include "CSceneManager.h"

#include "CTimeMgr.h"

#include "Texture.h"
#include "TextureManager.h"

#include "CTimeMgr.h"			
#include "Animator.h"
#include "Animation.h"

CutSceneObject::CutSceneObject()
	:m_cutscenetime(0)
	, index(0)
{
	
	//texture 로딩
	pTextureCutScene[0] = TextureManager::GetInstance()->LoadTexture(L"cutscene1", L"texture\\op_1.bmp");
	pTextureCutScene[1] = TextureManager::GetInstance()->LoadTexture(L"cutscene2", L"texture\\op_2.bmp");
	pTextureCutScene[2] = TextureManager::GetInstance()->LoadTexture(L"cutscene3", L"texture\\op_3.bmp");
	pTextureCutScene[3] = TextureManager::GetInstance()->LoadTexture(L"cutscene4", L"texture\\op_4.bmp");
}

CutSceneObject::~CutSceneObject()
{

}

///Update함수가 먼저 실행되고, Render함수가 나중에 실행된다
void CutSceneObject::Update()
{

	//for문 안써, 시간에 따른 index 증가

	//시간정보
	CTimeManager::GetInstance()->GetfDT();		///CTimeManager::GetInstance()를 쓰는 이유: 객체(CTimeManager타입인 객체 mgr)를 CTimeManager에서 가져온다
	m_cutscenetime += CTimeManager::GetInstance()->GetfDT();/// float를 리턴하니까 GetfDT()로 끝나더라도 float값이다
	//일정시간 경과 후 index 증가
	if (m_cutscenetime >= 1.0f)
	{
		index++;
		m_cutscenetime = 0.f;
	}

	//index=3 되면.... start 씬으로 넘어간다. 
	if (index >= 4)
	{
		ChangeScene(SCENE_TYPE::START);
	}

}

void CutSceneObject::Render(HDC _dc)
{
	///index가 3보다 크면, 배열이 out of range가 되어 pTextureCutScene[3]에 쓰레기값이 들어가게된다. 그래서 그냥 죽는 문제가 발생했었다
	///이때 예외처리를 해서, update가 실행, finalupdate가 실행, render가 실행된다
	/// update에서 인덱스 증가시키면, 3이 되면 changescene 하는데, 바로 changescene 되는 것이 아니라, render된 후 changescene이 일어난다
	/// 증가된 index(3보다 크거나 같은 값)가 render에 도달하면 문제가 된다, 그 index로 그리려면 문제가 생긴다
	/// 그러니, 예외처리를 한거다 return;만 하면, 아무것도 안보내니까 문제가 안생긴거다
	if (index >= 4)
	{
		return;
	}

	TransparentBlt(
		_dc
		, (int)0
		, (int)0
		, (int)1920
		, (int)1080
		, pTextureCutScene[index]->GetDC()
		, (int)0
		, (int)0
		, (int)pTextureCutScene[index]->Width()			///직접 구하지 않고, 미리 만들어놓은 함수로 텍스쳐 이미지의 폭, 높이 구할 수 있다
		, (int)pTextureCutScene[index]->Height()
		, RGB(255, 0, 255)
	);

}
