#pragma once
#ifndef GAME_ENTRY
#define GAME_ENTRY
#include <ctime>
#include <vector>
#include <math.h>
#include<atlconv.h>
#include "D2DDraw.h"
#include "Audio.h"
#pragma warning(disable:4005)
#pragma warning(disable:4091)
#pragma warning(disable:4616)
#pragma warning(disable:4083)
#pragma warning(disable:4018)
//#pragma warning(disable:C4993)
//#pragma warning(disable:C4988)
//#pragma warning(disable:C4983)
//#pragma warning(disable:C4978)
//#pragma warning(disable:C4972)
//#pragma warning(disable:C4967)
//#pragma warning(disable:C4962)
//#pragma warning(disable:C4616)
#define GAME_START 1
#define GAME_RUN 2
#define GAME_END 3
#define LCURSORSINGLECLICK 1  //单击
#define LCURSORDOUBLECLICK 2  //双击
#define LCURSORPRESSDOWN   3  //按下
#define WINWIDTH 1066
#define WINHEIGHT 600
class GAMES;
class GAMESCENE;
#include "ToolSet.h"
#define DSTORYOBJ(p) if(p) free(p);
#ifndef _SCENEHEAD_
#define _SCENEHEAD_

#endif


class GAMES
{
	GAMES()
	{

	}
	static GAMES *poi_Game;
	class _GAMES
	{
	public:
		~_GAMES()
		{
			if (GAMES::poi_Game)
				delete GAMES::poi_Game;
		}
	};
	static _GAMES VoidGame;
public:
	static GAMES *GetInstance()
	{
		if (!poi_Game)
		{
			poi_Game = new GAMES;
			poi_Game->var.MTS = new MyToolSet;
		}
		return poi_Game;
	}
	static struct Over_Variable
	{
		BMDRAWMTL        MTS;    //Direct绘制结构
		Audio_Music      AM;     //音频播放结构
		HWND             hWnd;   //主窗口DC
		DWORD            Pre_Fre,//帧数间隔时间
			             Cur_Fre;
		INT              Width,  //游戏宽高
			             Height;
	};
	ATOM MyRegisterClass(HINSTANCE hInstance);   //初始化与创建窗口
	//WORD为unsigned short型   表示一个双字节字符
	BOOL InitInstance(HINSTANCE, int);           //初始化窗口相关数据
	void ResourceLoad();      //资源加载与开始动画播放
	BOOL Run();               //游戏运行
	void AddScene(char *, GAMESCENE*);
	Over_Variable var;        //全局变量,几乎所有功能都会用到
	Point2D *BeginScene;      //开始场景所使用的图片
	std::map<CHAR *, GAMESCENE*>Scene;   //场景索引结构
	std::map<CHAR *, GAMESCENE*>::iterator CurScene;   //场景查找结构
};


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#endif