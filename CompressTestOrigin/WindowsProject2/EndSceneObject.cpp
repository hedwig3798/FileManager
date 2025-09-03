///엔딩에 쓸 오브젝트를 만든다
#include "pch.h"
#include "EndSceneObject.h"

#include "CSceneManager.h"

#include "CTimeMgr.h"

#include "Texture.h"
#include "TextureManager.h"

#include "CTimeMgr.h"			
#include "Animator.h"
#include "Animation.h"
#include "SoundManager.h"

EndSceneObject::EndSceneObject()
	:m_endscenetime(0)
	, index(0)
{
	pTextureEndScene[0] = TextureManager::GetInstance()->LoadTexture(L"endscene1", L"texture\\ed_1.bmp");
	pTextureEndScene[1] = TextureManager::GetInstance()->LoadTexture(L"endscene2", L"texture\\ed_2.bmp");
	pTextureEndScene[2] = TextureManager::GetInstance()->LoadTexture(L"endscene3", L"texture\\ed_3.bmp");
	pTextureEndScene[3] = TextureManager::GetInstance()->LoadTexture(L"endscene4", L"texture\\ed_4.bmp");
	//pTextureEndScene[4] = TextureManager::GetInstance()->LoadTexture(L"endscene5", L"texture\\ed_5.bmp");
}

EndSceneObject::~EndSceneObject()
{
}

///Update함수가 먼저 실행되고, Render함수가 나중에 실행된다
void EndSceneObject::Update()
{

	//for문 안써, 시간에 따른 index 증가

	//시간정보
	CTimeManager::GetInstance()->GetfDT();						///CTimeManager::GetInstance()를 쓰는 이유: 객체(CTimeManager타입인 객체 mgr)를 CTimeManager에서 가져온다
	m_endscenetime += CTimeManager::GetInstance()->GetfDT();	/// float를 리턴하니까 GetfDT()로 끝나더라도 float값이다
	//일정시간 경과 후 index 증가
	if (m_endscenetime >= 1.0f)
	{
		index++;
		m_endscenetime = 0.f;
	}

	//index=3 되면.... start 씬으로 넘어간다. 
	if (index >= 4)
	{
		ChangeScene(SCENE_TYPE::CREDIT);
		SoundManager::GetInstance()->Stop(SOUND_CHANNAL::BGM);

	}

}

void EndSceneObject::Render(HDC _dc)
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
		, pTextureEndScene[index]->GetDC()
		, (int)0
		, (int)0
		, (int)pTextureEndScene[index]->Width()			///직접 구하지 않고, 미리 만들어놓은 함수로 텍스쳐 이미지의 폭, 높이 구할 수 있다
		, (int)pTextureEndScene[index]->Height()
		, RGB(255, 0, 255)
	);

}


