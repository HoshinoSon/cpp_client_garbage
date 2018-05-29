#pragma once
#ifndef _CONPONENT_
#define _CONPONENT_
#include "GameEntry.h"
#define RETURNPREVIOUS -1
class GAMES;

class BASEBUTTOM
{
protected:
	GAMES *m_Game;      //游戏主框架
	RECT Pos;			//组件所在位置
	Point2D *m_NotState;        //无状态
	Point2D *m_PassState;       //鼠标经过
	Point2D *m_DownState;		//鼠标按下
	TOOLSET *m_Tool;            //工具库
	bool m_State;               //组件状态 true开启,false关闭
	float m_Angle;				//组件旋转角度
	float m_Opacity;			//组件透明度
public:
	BASEBUTTOM();
	virtual BOOL GetState()
	{
		return m_State;
	}
	virtual void SetState(BOOL state)
	{
		m_State = (bool)state;
	}
	virtual bool CurJudge(PointXY &t_CurPos);
	virtual void PosFollowWinRect();
	virtual void DrawImage();
	virtual void InitObject() = 0;
	virtual void Paint() = 0;
	virtual bool ObjectInstance(WORD t_type) = 0;
	virtual RECT GetPos();
	virtual bool Destory();
	virtual void ResetPos()
	{};
};

class CONPONENTBUTTOM
{
private:
	INT m_State;
	std::vector<char *>m_ListFind;
	std::map<char*, BASEBUTTOM*>m_Conponent;
	std::map<char*, BASEBUTTOM*>::iterator m_Find;
public:
	//设置、加入组件,1 : 组件名(可用作查找) 2: 组件实例   
	bool SetComponent(char* t_conponentname, BASEBUTTOM*conponentinstance);
	//获取组件体的编号
	INT GetState();
	//设置组件的编号
	void SetState(int t_state);
	//查找组件 1: 组件名
	BASEBUTTOM* Find(char *t_conponentname);
	//对组件进行点击判断
	BOOL CurPosJudge(Point2DXY t_CurPos, WORD t_type);
	//绘制组件图标
	void Paint();
	//销毁组件体
	void Destory();
	//关闭所有组件
	void CloseConponent();
	//打开所有组件
	void OpenConponent();
};

#endif