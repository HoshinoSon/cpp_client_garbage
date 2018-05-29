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
#define LCURSORSINGLECLICK 1  //����
#define LCURSORDOUBLECLICK 2  //˫��
#define LCURSORPRESSDOWN   3  //����
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
		BMDRAWMTL        MTS;    //Direct���ƽṹ
		Audio_Music      AM;     //��Ƶ���Žṹ
		HWND             hWnd;   //������DC
		DWORD            Pre_Fre,//֡�����ʱ��
			             Cur_Fre;
		INT              Width,  //��Ϸ���
			             Height;
	};
	ATOM MyRegisterClass(HINSTANCE hInstance);   //��ʼ���봴������
	//WORDΪunsigned short��   ��ʾһ��˫�ֽ��ַ�
	BOOL InitInstance(HINSTANCE, int);           //��ʼ�������������
	void ResourceLoad();      //��Դ�����뿪ʼ��������
	BOOL Run();               //��Ϸ����
	void AddScene(char *, GAMESCENE*);
	Over_Variable var;        //ȫ�ֱ���,�������й��ܶ����õ�
	Point2D *BeginScene;      //��ʼ������ʹ�õ�ͼƬ
	std::map<CHAR *, GAMESCENE*>Scene;   //���������ṹ
	std::map<CHAR *, GAMESCENE*>::iterator CurScene;   //�������ҽṹ
};


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#endif