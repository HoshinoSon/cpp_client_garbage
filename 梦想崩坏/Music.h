#pragma once
#ifndef _MUSIC_
#define _MUSIC_
#define OPENMUSICROOM 1
#define CLOCEMUSICROOM 0
#define BACKSSTATE -1

#define ONESONGCURCULATE 1
#define LISTINGCURCULATE 2
#define ORDERPLAY 3

#define CURRENTPLAY 1
#define STOPPLAY 2

#define MUSIC_QUIT         0x01
#define MUSIC_MINIMIZE     0x02
#define MUSIC_STRIP		   0x03
#define MUSIC_POS		   0x04
#define MUSIC_PLAY		   0x05

#include "Buttom.h"
#include <map>
#include <io.h>
using namespace std;
class GAMES;

struct MusicUI
{
	Point2D *image;
	char *filename;
	char *musicname;
	int Lenth;
};

struct MUSICINFORMATION
{
	string m_Name;
	char *m_FileWay;
};

struct CURPLAYMUSIC
{
	string m_Name;
	float m_Lenth;
	float m_Loaction;
};

class MUSIC
{
private:
	CAudioManager Fmusic;
	MUSIC()
	{
		InitMusic();
		/*	memset(m_CurPlay.m_Name, 0, 64);*/
	}
	static MUSIC *music;
	class _MUSIC
	{
	public:
		~_MUSIC()
		{
			if (MUSIC::music)
				delete MUSIC::music;
		}
	};
	//����ģʽ : ����ѭ��,���,˳��
	int m_PlayModel;
	//����
	Point2D *m_BackImage;
	//��ǰ���ֲ���λ��
	static _MUSIC _music;
	//��ǰ���ڲ��ŵ�����
	CURPLAYMUSIC m_CurPlay;
	//����UI
	vector<MusicUI*>MusicGather;
	vector<MusicUI*>::iterator CurPlayUI;
	//�����������
	vector<WCHAR *>MusicName;
	map<string, MUSICINFORMATION* >m_MusicLibrary;
	map<string, MUSICINFORMATION* >::iterator m_LibraryFind;
	//���߿�
	TOOLSET *tool;
	//��
	Point2D *BackStrip[2];
	//���ʵ��
	CONPONENTBUTTOM *m_CPNInstance;
	//
	INT BackKey;
	INT MusicKey;
	GAMES *m_Game;
	MusicUI *Reimu;
	BOOL m_MusicState;
	BOOL m_PlayState;
	BOOL m_PlayListing;
public:
	static MUSIC *GetInstance()
	{
		if (!music)
			music = new MUSIC;
		return music;
	}
	//��ȡ����״̬
	int GetPlayState();
	//���ò���״̬
	void SetPlayState(int t_state);
	//��ȡ������״̬
	int GetMusicState();
	//�򿪰���
	void OpenKey();
	//�رհ���
	void CloceKey();
	//��������
	void OpenMusicRoom();
	//�ر�������
	void CloceMusicRoom();
	//������������
	void BACKSSTATEMusicRoom();
	//���Ĳ���ģʽ
	void SetPlayModel(int t_model);
	//��ȡ������״̬
	BOOL GetMusicRoomState();
	//������¼�
	BOOL CurSorJudge(Point2DXY t_CurPos, WORD t_type);
	//��ȡ������
	INT GetConponentCompare();
	//��ȡ��ǰ���ڲ��ŵ�����
	string *GetCurPlay();
	//����һ��������
	void PlayOneMusic(const char *filename);
	//�������ŵ�ǰ����
	void ContinueLoopMusic();
	//ֹͣ����
	void StopLoopMusic();
	//���ò���λ��
	void SetPlayPos(unsigned int pos);
	//��ȡ��ǰ����λ��
	float GetPlayPos();
	//����ѭ������
	void PlayLoopMusic(const char *filename);
	//��ȡ���ֳ���
	int GetLlenth();
	//��ȡһ������������
	int GetOneVolume();
	//��ȡѭ����������
	int GetLoopVolume();
	//����һ������������
	void SetOneVolume(int num);
	//����ѭ����������
	void SetLoopVolume(int num);
	//����ѭ������
	void LoadLoopMusic(char *filename, const char *fileway, bool NOImage);
	//����һ��������
	void LoadOneMusic(const char *filename, const char *fileway);
	//����������ͼ
	void LoadMusicUI(MusicUI *&UIHead);
	//��������
	void AddMusic(WCHAR *filename);
	//��ʼ������ʵ��
	void InitMusic();
	//������
	void MusicMoon();
	//��������������ͼ
	void Paint();
	//���ڴ�ɾ����ǰ���ŵ�����
	void DeleteCurPlayMusic();
	//������һ������
	void PlayNextMusic();
	//�Ƿ񲥷���һ��
	void WhetherNext();
	//���������б�
	void LoadMusicFile();
};

DWORD WINAPI MusicRoom(LPVOID lpParam);
#endif