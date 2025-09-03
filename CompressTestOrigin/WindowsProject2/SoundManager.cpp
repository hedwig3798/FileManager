#include "pch.h"
#include "SoundManager.h"

#include "pch.h"
#include "SoundManager.h"
#include <fmod_errors.h>


SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::GetInstance()	            // 메모리할당하는 함수
{
	if (instance == NULL)
		instance = new SoundManager;
	return instance;
}
SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	result = System_Create(&m_System);								///시스템을 생성한다(&pFmod) 
	ErrorCheck(result);												///에러체크  
	result = m_System->init(128, FMOD_INIT_NORMAL, NULL);			///시스템 안에서 초기화 함수를 가져온다.
	ErrorCheck(result);												///에러체크  
}

void SoundManager::Loading()
{
	result = m_System->createSound("content\\sound\\main.wav", FMOD_LOOP_NORMAL, NULL, &m_sound[BACKGROUND_MAINTITLE]);		//pfmod->createsound은 시스템에서 사운드는 함수를 가져와 이름, 무한 루프, 
	ErrorCheck(result);																											//에러체크  
	result = m_System->createSound("content\\sound\\ingame_.wav", FMOD_LOOP_NORMAL, NULL, &m_sound[BACKGROUND_INGAME]);
 	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\ending.wav", FMOD_LOOP_NORMAL, NULL, &m_sound[BACKGROUND_ENDING]);
 	ErrorCheck(result);																	
	result = m_System->createSound("content\\sound\\fire.wav", FMOD_DEFAULT, NULL, &m_sound[EFFECT_ARROW]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\flame.wav", FMOD_DEFAULT, NULL, &m_sound[EFFECT_FIRE]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\poison.wav", FMOD_DEFAULT, NULL, &m_sound[EFFECT_POISON]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\spike.wav", FMOD_DEFAULT, NULL, &m_sound[EFFECT_SPIKE_TRAP]);
	ErrorCheck(result);

	//ACTION SOUND
	result = m_System->createSound("content\\sound\\time.wav", FMOD_DEFAULT, NULL, &m_sound[EFFECT_TIMETRAVEL]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\click.wav", FMOD_DEFAULT, NULL, &m_sound[EFFECT_BUTTON]);
	ErrorCheck(result);

	//ENEMY SOUND 
	result = m_System->createSound("content\\sound\\guardian move.wav", FMOD_DEFAULT, NULL, &m_sound[ENEMYGUARDIAN_MOVE]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\guardian hit.wav", FMOD_DEFAULT, NULL, &m_sound[ENEMYGUARDIAN_HIT]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\spider move.wav", FMOD_DEFAULT, NULL, &m_sound[ENEMY_MOVE]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\spider hit.wav", FMOD_DEFAULT, NULL, &m_sound[ENEMY_DEAD]);
	ErrorCheck(result);

	//PLAYER SOUND
	result = m_System->createSound("content\\sound\\move.wav", FMOD_DEFAULT, NULL, &m_sound[PLAYER_MOVE]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\attack.wav", FMOD_DEFAULT, NULL, &m_sound[PLAYER_ATTACK]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\dead.wav", FMOD_DEFAULT, NULL, &m_sound[PLAYER_DEAD]);
	ErrorCheck(result);

	//EFFET
	result = m_System->createSound("content\\sound\\door.wav", FMOD_DEFAULT, NULL, &m_sound[DOOR]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\debuff.wav", FMOD_DEFAULT, NULL, &m_sound[DEBUFF]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\collapse.wav", FMOD_DEFAULT, NULL, &m_sound[COLLAPSE]);
	ErrorCheck(result);
	result = m_System->createSound("content\\sound\\ending.wav", FMOD_DEFAULT, NULL, &m_sound[ENDING]);
	ErrorCheck(result);

	//CREDIT
	result = m_System->createSound("content\\sound\\end.wav", FMOD_DEFAULT, NULL, &m_sound[SOUND_END]);
	ErrorCheck(result);
}
void SoundManager::Play(SOUND _type, SOUND_CHANNAL _channal)
{
	m_System->update();
	result = m_System->playSound(m_sound[_type], NULL, false, &m_channel[_channal]);			//플레이사운드에서 (노래[열거형], 채널그룹and채널, 정지, 채널)
	ErrorCheck(result);																			//에러 체크 박스
}

void SoundManager::Pause(SOUND_CHANNAL _channal)
{
	result = m_channel[_channal]->setPaused(true);
	ErrorCheck(result);
}

void SoundManager::Resume(SOUND_CHANNAL _channal)
{
	result = m_channel[_channal]->setPaused(false);
	ErrorCheck(result);
}

void SoundManager::Stop(SOUND_CHANNAL _channal)
{
	m_channel[_channal]->stop();
}

void SoundManager::Rlease()
{
	m_System->release();
}

void SoundManager::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		TCHAR szStr[256] = { 0 };
		MultiByteToWideChar(CP_ACP, NULL, FMOD_ErrorString(result), -1, szStr, 256);
		MessageBox(NULL, szStr, L"Sound Error", MB_OK);
	}
}
// 
// void SoundManager::volumeup()
// {
// 	if (m_volume < SOUND_MAX)
// 	{
// 		m_volume += SOUND_WEIGHT;
// 	}
// }
// 
// void SoundManager::volumedown()
// {
// 	if (m_volume > SOUND_MIN)
// 	{
// 		m_volume -= SOUND_WEIGHT;
// 	}
// }

void SoundManager::FinalRlease()
{
	m_System->release();
	m_System->close();
	delete instance;
}