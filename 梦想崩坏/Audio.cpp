#include "Fmod.h"
#include "Audio.h"
#include <Windows.h>

#include <process.h>
#include <stdlib.h>

#pragma comment(lib, "fmodvc.lib")

//am.PlayOnceAudio() 播放流音频
//am.StopLoopAudio("背景音乐3");  播放背景
//am.PlayLoopAudio("背景音乐4");
//加载背景音乐
//am.PushLoopAudio("背景音乐3", "audio\\3.mp3");
//am.PushLoopAudio("背景音乐4", "audio\\4.mp3");

//加载音效
//am.PushOnceAudio("音效1", "audio\\1.wav");
//am.PushOnceAudio("音效2", "audio\\2.wav");

CAudioManager::CAudioManager(int InitLoopVolume, int InitOnceVolume, int MaxChannel)
	:
	m_MaxChannel(MaxChannel),
	m_LoopVolume(InitLoopVolume),
	m_OnceVolume(InitOnceVolume)
{
	//FMOD初始化
	FSOUND_Init(44100, MaxChannel, 0);
}

CAudioManager::~CAudioManager()
{
	std::map<std::string, _LOOPAUDIO>::iterator i;
	for (i = m_LoopAudio.begin(); i != m_LoopAudio.end(); ++i)
		FSOUND_Stream_Close(i->second._s);

	std::map<std::string, _LOOPAUDIO>::iterator j;
	for (j = m_OnceAudio.begin(); j != m_OnceAudio.end(); ++j)
		FSOUND_Stream_Close(j->second._s);

	//FMOD关闭
	FSOUND_Close();
}

bool CAudioManager::PushLoopAudio(const char* Key, const char* AudioPath)
{
	std::string s = Key;

	//如果Key已经存在返回失败
	if (m_LoopAudio.find(Key) != m_LoopAudio.end())
		return false;

	_LOOPAUDIO la;

	//加载流式音频
	la._s = FSOUND_Stream_Open(AudioPath, FSOUND_LOOP_NORMAL, 0, 0);

	//216
	la.Lenth = FSOUND_Stream_GetLengthMs(la._s);
	//推入索引中
	if (la._s)
	{
		m_LoopAudio[s] = la;

		return true;
	}
	else
		return false;
}

int CAudioManager::GetMusicLenth()
{
	
	if (m_PlayingLoopAudio[0] == 0)
		return 0;
	return m_LoopAudio.find((std::string)m_PlayingLoopAudio)->second.Lenth;
}

bool CAudioManager::PushOnceAudio(const char* Key, const char* AudioPath)
{
	std::string s = Key;

	//如果Key已经存在返回失败
	if (m_OnceAudio.find(Key) != m_OnceAudio.end())
		return false;

	//加载音频样本
	_LOOPAUDIO pFS;
	pFS._s= FSOUND_Stream_Open(AudioPath, FSOUND_LOOP_OFF, 0, 0);

	if (pFS._s)
	{
		m_OnceAudio[s] = pFS;
		return true;
	}
	else
		return false;
}

bool CAudioManager::ReleaseLoopAudio(const char* Key)
{
	std::string s = Key;

	//没有找到
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if (i == m_LoopAudio.end())
		return false;

	FSOUND_Stream_Close(i->second._s);

	m_LoopAudio.erase(i);

	return true;
}

bool CAudioManager::ReleaseOnceAudio(const char* Key)
{
	std::string s = Key;

	//没有找到
	std::map<std::string, _LOOPAUDIO>::iterator i = m_OnceAudio.find(s);
	if (i == m_OnceAudio.end())
		return false;

	FSOUND_Stream_Close(i->second._s);

	m_OnceAudio.erase(i);

	return true;
}

void CAudioManager::ContinueCurrentPlay(unsigned int Postion)
{
	std::string s = m_PlayingLoopAudio;
	//FSOUND_Stream_Stop(m_LoopAudio.find(s)->second._s);
	FSOUND_Stream_Play(FSOUND_FREE, m_LoopAudio.find(s)->second._s);
	float f = (float)FSOUND_Stream_GetPosition(m_LoopAudio.find(s)->second._s);
	float x = (float)m_LoopAudio.find(s)->second.Lenth;
	float y = FSOUND_Stream_GetLength(m_LoopAudio.find(s)->second._s);
	x /= y;
	FSOUND_Stream_SetPosition(m_LoopAudio.find(s)->second._s, Postion / x);

}

int  CAudioManager::GetCurrentPlayPos()
{
	if (m_PlayingLoopAudio[0] == 0)
		return 0;
	std::string s = m_PlayingLoopAudio;
	float f = (float)FSOUND_Stream_GetPosition(m_LoopAudio.find(s)->second._s);
	float x = (float)m_LoopAudio.find(s)->second.Lenth;
	float y = FSOUND_Stream_GetLength(m_LoopAudio.find(s)->second._s);
	x /= y;
	float lenth = (f * (x)/* / 1000.0*/);
	return lenth;
}

bool CAudioManager::PlayLoopAudio(const char* Key)
{
	//如果当前有循环音频在播放返回失败
	if (m_PlayingLoopAudio.size() != 0)
	{
		std::string s = Key;
		FSOUND_Stream_Play(FSOUND_FREE, m_LoopAudio.find(s)->second._s);
		return false;
	}
	//无法找到Key所指定的音频则返回失败
	std::string s = Key;
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if (i == m_LoopAudio.end())
		return false;

	//设置当前正在播放的循环音频
	m_PlayingLoopAudio = s;

	//播放音频并得到声道
	i->second._c = FSOUND_Stream_Play(FSOUND_FREE, i->second._s);

	//设置音量
	FSOUND_SetVolume(i->second._c, m_LoopVolume);

	return true;
}

bool  CAudioManager::CloceLoopAudio()
{
	//无法找到Key所指定的音频则返回失败
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(m_PlayingLoopAudio);
	if (i == m_LoopAudio.end())
		return false;

	//设置当前不播放任何音频
	m_PlayingLoopAudio = "";

	//停止流式音频的播放
	FSOUND_Stream_Stop(i->second._s);

	//设置声道
	i->second._c = -1;

	return true;
}

bool CAudioManager::StopLoopAudio(const char* Key)
{
	std::string s = Key;

	//如果不是当前正在播放的音频返回失败
	if (m_PlayingLoopAudio != s)
		return false;

	//无法找到Key所指定的音频则返回失败
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if (i == m_LoopAudio.end())
		return false;

	//设置当前不播放任何音频
	//m_PlayingLoopAudio = "";

	//停止流式音频的播放
	FSOUND_Stream_Stop(i->second._s);

	//设置声道
	i->second._c = -1;

	return true;
}

bool CAudioManager::PlayOnceAudio(const char* Key)
{
	std::string s = Key;
	std::map<std::string, _LOOPAUDIO>::iterator i = m_OnceAudio.find(s);
	if (i == m_OnceAudio.end())
		return false;

	//播放音频并设置音量
	i->second._c = FSOUND_Stream_Play(FSOUND_FREE, i->second._s);
	return true;
}

int CAudioManager::GetLoopVolume()
{
	//返回循环音频音量
	return m_LoopVolume;
}

bool CAudioManager::SetLoopVolume(int Volume)
{
	//如果不在合法范围内返回失败
	if (Volume < 0 || Volume > 255)
		return false;
	//得到音量
	m_LoopVolume = Volume;
	//如果当前有循环音频在播放
	if (m_PlayingLoopAudio != std::string(""))
	{
		//设置该音频的音量
		FSOUND_SetVolume(m_LoopAudio.find(m_PlayingLoopAudio)->second._c, m_LoopVolume);
	}
	return true;
}

int CAudioManager::GetOnceVolume()
{
	//返回非循环音频音量
	return m_OnceVolume;
}

bool CAudioManager::SetOnceVolume(int Volume)
{
	//如果不在合法范围内返回失败
	if (Volume < 0 || Volume > 255)
		return false;

	//得到音量
	m_OnceVolume = Volume;
	return true;
}

void CAudioManager::DeleteMusic(const char *Key)
{
	std::string s = Key;
	FSOUND_Stream_Close(m_LoopAudio.find(m_PlayingLoopAudio)->second._s);
}

