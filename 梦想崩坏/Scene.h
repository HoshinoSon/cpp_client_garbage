#pragma once
#ifndef _SCENE_
#define _SCENE_
#include "GameEntry.h"
#include "Music.h"
#include "Buttom.h"
#include <list>
#include "CConponent.h"
//#include "Role.h"

using namespace std;
class GAMES;
class CCONPONENT;
struct MAP
{
	INT Image;
	INT X;
	INT Y;
};


class GAMESCENE
{
protected:
	struct BG_Music
	{
		//CAudioManager Music;
		char *Start_FileName;
		char *Boss_FileName;
	};
	//std::map<char *, CONPONENTBUTTOM *>m_CPNInstance;
	//按下的位置
	PointXY m_PressDown;
	//鼠标位置
	PointXY m_CurPos;
	//是否初始化
	BOOL m_InitInstance;
	CCONPONENT *m_Conponent;
	//背景音乐
	BG_Music m_Bg_music;
	//弹幕库
	DMK *m_Dmk;
	//音乐库
	MUSIC *m_Music;
	//强制退出场景
	bool m_ForceBreak;
	//
	Point2D *m_TextrueMap[14];
	//刷新时间
	MyTimer m_Time;
	//工具库
	TOOLSET *m_Tool;
	//地图
	vector<MAP>::iterator m_pMap;
	//主体框架结构
	GAMES *m_Game;
	//人物类
	ROLE *m_Role;
	int m_Select_p;
	//FIGURE *Enemy;
	//背景
	Point2D *BG;
	//当前窗口位置
	INT Cur_O_Pos;
	//当前背景位置
	INT Cur_S_Pos;
public:


	virtual CCONPONENT *GetConponent();
	//将场景初始化为0,表示未初始化
	virtual void SetInitKey();
	//将当前场景强制结束
	virtual void ForceBreak();
	//获取鼠标位置
	virtual PointXY *GetCurSorPos();
	//碰撞
	virtual void Collision(Point2DXY, Point2DXY) = 0;
	//绘制
	virtual void MyPaint() = 0;
	//初始化
	virtual BOOL InitScene() = 0;
	virtual int InitButtom() { return true; };
	//运行场景
	virtual BOOL Run() = 0;
	//结束场景
	virtual void End() = 0;
	//鼠标按下
	virtual void PressDown(PointXY &t_Pos);
	virtual void UpCursor();
	//获取按下的位置
	virtual PointXY *GetPressDown();
	//设置当前鼠标位置
	virtual void SceneSetCurSorPos();
	//绘制组件
	virtual void ConponentPaint();
	//鼠标点击判断
	virtual void ButtomJudge(Point2DXY t_CurPos, WORD t_type);
	//设置屏幕坐标 注: 数据为反着   如果想要X轴+10像素   那么填写-10 
	virtual void SetBGPos(int x, int y) {};
	//获取屏幕坐标 
	virtual Point2DXY GetBGpos() { return false; };
};

#endif