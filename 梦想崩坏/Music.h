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
	//播放模式 : 单曲循环,随机,顺序
	int m_PlayModel;
	//背景
	Point2D *m_BackImage;
	//当前音乐播放位置
	static _MUSIC _music;
	//当前正在播放的音乐
	CURPLAYMUSIC m_CurPlay;
	//音乐UI
	vector<MusicUI*>MusicGather;
	vector<MusicUI*>::iterator CurPlayUI;
	//保存的音乐名
	vector<WCHAR *>MusicName;
	map<string, MUSICINFORMATION* >m_MusicLibrary;
	map<string, MUSICINFORMATION* >::iterator m_LibraryFind;
	//工具库
	TOOLSET *tool;
	//条
	Point2D *BackStrip[2];
	//组件实例
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
	//获取播放状态
	int GetPlayState();
	//设置播放状态
	void SetPlayState(int t_state);
	//获取音乐厅状态
	int GetMusicState();
	//打开按键
	void OpenKey();
	//关闭按键
	void CloceKey();
	//打开音乐厅
	void OpenMusicRoom();
	//关闭音乐厅
	void CloceMusicRoom();
	//将音乐厅挂起
	void BACKSSTATEMusicRoom();
	//更改播放模式
	void SetPlayModel(int t_model);
	//获取音乐厅状态
	BOOL GetMusicRoomState();
	//鼠标点击事件
	BOOL CurSorJudge(Point2DXY t_CurPos, WORD t_type);
	//获取组件编号
	INT GetConponentCompare();
	//获取当前正在播放的音乐
	string *GetCurPlay();
	//播放一次性音乐
	void PlayOneMusic(const char *filename);
	//继续播放当前音乐
	void ContinueLoopMusic();
	//停止播放
	void StopLoopMusic();
	//设置播放位置
	void SetPlayPos(unsigned int pos);
	//获取当前播放位置
	float GetPlayPos();
	//播放循环音乐
	void PlayLoopMusic(const char *filename);
	//获取音乐长度
	int GetLlenth();
	//获取一次性音乐音量
	int GetOneVolume();
	//获取循环音乐音量
	int GetLoopVolume();
	//设置一次性音乐音量
	void SetOneVolume(int num);
	//设置循环音乐音量
	void SetLoopVolume(int num);
	//加载循环音乐
	void LoadLoopMusic(char *filename, const char *fileway, bool NOImage);
	//加载一次性音乐
	void LoadOneMusic(const char *filename, const char *fileway);
	//加载音乐贴图
	void LoadMusicUI(MusicUI *&UIHead);
	//加入音乐
	void AddMusic(WCHAR *filename);
	//初始化音乐实例
	void InitMusic();
	//音乐厅
	void MusicMoon();
	//绘制音乐厅内贴图
	void Paint();
	//从内存删除当前播放的音乐
	void DeleteCurPlayMusic();
	//播放下一首音乐
	void PlayNextMusic();
	//是否播放下一首
	void WhetherNext();
	//加载音乐列表
	void LoadMusicFile();
};

DWORD WINAPI MusicRoom(LPVOID lpParam);
#endif