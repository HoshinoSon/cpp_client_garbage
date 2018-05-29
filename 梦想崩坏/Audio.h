#pragma once
#pragma once
#pragma once
#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <string>
#include <map>
#include "fmod.h" //FMOD��һ���ƽ̨����Ƶ����
#define Audio_Music CAudioManager

class CAudioManager
{
private:
	//ѭ����Ƶ����
	struct _LOOPAUDIO
	{
		//������
		FSOUND_STREAM* _s; //��Ƶ��

						   //����
		int _c;
		int Lenth;
		//����:����
		_LOOPAUDIO()
			:
			_s(0),
			_c(-1)
		{}
	};
	std::string m_PlayingLoopAudio; //���ڲ��ŵ�ѭ������
	int m_MaxChannel; //��������
	int m_LoopVolume; //ѭ����������(0~255)
	int m_OnceVolume; //��ѭ����������(0~255)
	int m_State;
	

public:
	std::map<std::string, _LOOPAUDIO> m_LoopAudio; //ѭ�����ּ���
	std::map<std::string, _LOOPAUDIO> m_OnceAudio; //��ѭ�����ּ���
	//����:����
	//����1:��ʼѭ����Ƶ����(��������)
	//����2:��ʼ��ѭ����Ƶ����(��Ч)
	//����3:��������
	CAudioManager(int InitLoopVolume = 127, int InitOnceVolume = 127, int MaxChannel = 32);

	//����:����
	virtual ~CAudioManager();

	//����:����ѭ������
	//����1:ѭ������ID
	//����2:ѭ�������ļ�·��
	//����:trueΪ�ɹ�,falseΪʧ��
	bool PushLoopAudio(const char* Key, const char* AudioPath);

	//����:���ط�ѭ������
	//����1:��ѭ������ID
	//����2:��ѭ�������ļ�·��
	//����:trueΪ�ɹ�,falseΪʧ��
	bool PushOnceAudio(const char* Key, const char* AudioPath);

	//����:�ͷ�ѭ������
	//����1:ѭ������ID
	//����:trueΪ�ɹ�,falseΪʧ��
	bool ReleaseLoopAudio(const char* Key);

	//����:�ͷŷ�ѭ������
	//����1:��ѭ������ID
	//����:trueΪ�ɹ�,falseΪʧ��
	bool ReleaseOnceAudio(const char* Key);

	//����:����ѭ������
	//����1:ѭ������ID
	//����:trueΪ�ɹ�,falseΪʧ��
	bool PlayLoopAudio(const char* Key);

	//����:ֹͣѭ������
	//����1:ѭ������ID
	//����:trueΪ�ɹ�,falseΪʧ��
	bool StopLoopAudio(const char* Key);

	//����:���ŷ�ѭ������
	//����1:��ѭ������ID
	//����:trueΪ�ɹ�,falseΪʧ��
	bool PlayOnceAudio(const char* Key);

	//����:�õ�ѭ����������
	//����:ѭ����������
	int GetLoopVolume();

	//����:����ѭ����������
	//����:trueΪ�ɹ�,falseΪʧ��
	bool SetLoopVolume(int Volume);

	//����:�õ���ѭ����������
	//����:��ѭ����������
	int GetOnceVolume();

	//����:���÷�ѭ����������
	//����:trueΪ�ɹ�,falseΪʧ��
	bool SetOnceVolume(int Volume);

	//�ر����ڲ��ŵ�����   KeyΪ���ڲ��ŵ�������
	bool CloceLoopAudio();
	
	//��ȡ��ǰ�������ֵ�ʱ��
	int GetMusicLenth();

	//��ȡ��ǰ�ڲ����е����������ڲ��ŵ�λ��
	int GetCurrentPlayPos();

	//�������ò���λ��
	void ContinueCurrentPlay(unsigned int Postion);

	//�����ֿ����Ƴ�Keyָ��������
	void DeleteMusic(const char *Key);
};

#endif