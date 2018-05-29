#pragma once
#ifndef TOOL_SET
#define TOOL_SET
#define pi 3.1415926535  
#define SLOPE_ONE 0x01
#define SLOPE_TWO 0x02
#define SLOPE_THREE 0x03
#define KEY_KEEP_DOWN    0 //持续按下
#define KEY_CURRENT_DOWN 1 //当前按下
#define KEY_KEEP_UP      2 //持续放开
#define KEY_CURRENT_UP   3 //当前放开
#define MONSTERBULLET 0x01  //怪物发射
#define FIGUREBULLET 0x02   //人物发射
#define STRAIGHTTYPE 0x01
#define CURVATYPE 0x02
#include <sys/timeb.h>
using namespace std;

typedef long long int Int64;
typedef long int Int32;
typedef time_t Time_Value;


class ROLE;
struct Angle
{
	double slope;
	float vk_x;
	float vk_y;
	float angle;
	bool key;
};
struct MyTimer
{
	float Cur;
	float Pre;
	float Interval;
};


struct SKILLTYPE
{
	MyTimer Times;
	INT Type;
};

typedef struct SKILL_TYPE_CONTAIN
{
	//顺序执行
	SKILLTYPE Type1;
	SKILLTYPE Type2;
	SKILLTYPE Type3;
	SKILLTYPE Type4;
}STC;

typedef struct BEZIER_CONTROL_NODE
{
	PointCoorDinate node_one;
	PointCoorDinate node_two;
	PointCoorDinate node_three;
	PointCoorDinate node_four;
}*pBCN, nBCN;

//-------------------------------------------------直线池----------------------------------------------

struct STRAIGHT
{
	INT Harm;
	PointXY LocaTion; //当前位置
	PointXY VK;       //增量位置
	FLOAT Angle;        //图片角度
	STC Type;           //发射物附加状态
	INT WhatIsBullet;   //谁发射的？
	INT Image;          //图片
	MyTimer ExecuteType;//什么时候开始执行发射物的附加状态
};

typedef struct DMK_SA_MEMORI
{
	DMK_SA_MEMORI *next;
	DMK_SA_MEMORI *prev;
	STRAIGHT data;
}*pDMK_SA_MEMORI;

typedef pDMK_SA_MEMORI DMKSAMMR;
typedef DMK_SA_MEMORI newDMKSAMMR;



//-------------------------------------------------曲线池------------------------------------------------
struct CURVA
{
	INT Harm;
	pBCN Bezier_node;   //第一个和第四个是起始点和目标点,第二个第三个为控制点
	PointXY ObjectPos;//当前位置
	PointXY VK;       //增量位置
	INT Image;          //图片
	INT WhatIsBullet;   //谁发射的？
	STC Type;           //附加状态
	DWORD Run;          //未知
	MyTimer ExecuteType;//什么时候开始执行附加状态
};


typedef struct DMK_CURVA_MEMORI
{
	DMK_CURVA_MEMORI *next;
	DMK_CURVA_MEMORI *prev;
	CURVA data;
}*pDMK_CV_MEMORI;

typedef pDMK_CV_MEMORI DMKCVMMR;
typedef DMK_CURVA_MEMORI newDMKCVMMR;

class TOOLSET;
class DMK
{
private:
	DMK()
	{
		InitMmr();
	}
	static DMK *dmk;
	class _DMK
	{
	public:
		~_DMK()
		{
			if (DMK::dmk)
				delete DMK::dmk;
		}
	};
	static _DMK _VoidDmk;
public:
	MyTimer RunTime;
	TOOLSET *tool;
	static DMK *GetDmkInstance()
	{
		if (!dmk)
		{
			dmk = new DMK;
		}
		return dmk;
	}

	void InitMemoriSA(DMKSAMMR &mmr);
	void *NewSA(DMKSAMMR &Head);
	void DelSA(DMKSAMMR Node);
	//---------------------------------------------------END-------------------------------------------------



	void InitMemoriCV(DMKCVMMR &mmr);
	void *NewCV(DMKCVMMR &Head);
	void DelCV(DMKCVMMR Node);
	//--------------------------------------------------END---------------------------------------------------


	//--------------------------------------------直线类型函数声明--------------------------------------------
	//圆形
	void BulletRoundNess(DMKSAMMR &head, CONST Point2D _image, CONST SKILLTYPE _st,
		CONST INT _angle, INT Slope, INT what_is_bullet, PointXY Pos, STC stc, INT image);
	//扇形
	void BulletSector(DMKSAMMR &head, INT _angle, INT radius, Point2D _image, const SKILLTYPE _st, const MyTimer _times, INT Slope);
	//分成2个
	void FissionMirroring(DMKSAMMR &head, DMKSAMMR &node, INT angle, Point2D _image, const SKILLTYPE _st, INT Slope);
	//分成一堆
	void FissionDisperse(size_t size, INT angle, INT Slope);
	//--------------------------------------------------END---------------------------------------------------

	//--------------------------------------------曲线类型函数声明--------------------------------------------
	void BezierCurva(Point2DXY &object_pos, const Point2DXY location_state, const Point2DXY location1,
		const Point2DXY location2, const Point2DXY location_goal, INT Slope);
	void BulletRoundNess(CURVA type, INT Slope);					   //圆形
	void BulletSector(INT angle, INT Slope);						   //扇形
	void FissionMirroring(DMKCVMMR &head, INT angle, INT Slope);                      //分成2个
	void FissionDisperse(DMKCVMMR &head, size_t size, INT angle, INT Slope);		   //分成一堆
																					   //--------------------------------------------------END---------------------------------------------------

																					   //------------------------------------------------变量声明------------------------------------------------
	DMKCVMMR dmkcvmmr;
	DMKSAMMR dmksammr;

	DMKSAMMR DCMFHead;
	DMKSAMMR DSMMHead;
	//DMKSAMMR *GetSA()

	Point2D *FSkillChartLet[10];
	Point2D *MSkillChartLet[10];
	//--------------------------------------------------END---------------------------------------------------

	//------------------------------------------------函数声明------------------------------------------------
	void *NewStraight();
	void *NewCurva();
	void SetTimer(MyTimer &times, INT cur, INT pre, INT interval);
	void SetSKILLTYPE(SKILLTYPE &st, MyTimer times, INT type);
	void SetSTC(STC &skill_type, SKILLTYPE type1, SKILLTYPE type2, SKILLTYPE type3, SKILLTYPE type4);
	void Draw();
	void Run();
	void InitMmr();

	bool Means_two_m(Angle slope, int &cur, int &max, INT what_is_bullet, PointXY Pos, STC, INT);
	Angle Means_two_s(Angle, int &, int &, INT, PointXY, STC, INT);
	//--------------------------------------------------END---------------------------------------------------
};

//--------------------------------------------------工具类----------------------------------------------------

class Input
{
	Input()
	{

	}
	int *Key;
	int *KeyState;
	int KeyNum;
	static Input * m_Input;
	class _Input
	{
	public:
		~_Input()
		{
			if (Input::m_Input)
			{
				delete Input::m_Input;
			}
		}
	};
	static _Input void_Input;
public:
	static Input * GetInstance()
	{
		if (!m_Input)
		{
			m_Input = new Input;
		}
		return m_Input;

	}
	//初始化按键
	void IniInputMgr(int num, int *pKey);
	//检测按键
	void CheckKeyState();
	//获取按键信息
	int MyGetKeyState(int pos);

};

//------------------------------------------------工具函数声明------------------------------------------------
class Clock
{
	static Clock *m_Clock;
	Clock();
	class _Clock
	{
	public:
		~_Clock()
		{
			if (Clock::m_Clock)
				delete m_Clock;
		}
	};
	_Clock _m_Clock;
	Time_Value startTime;
	Time_Value CurTime;
public:
	static Clock *GetClock()
	{
		if (!Clock::m_Clock)
			Clock::m_Clock = new Clock;
		return Clock::m_Clock;
	}
	Time_Value GetSustainTime();
	Time_Value UpTime();
};


class TOOLSET
{
	TOOLSET()
	{

	}
	static TOOLSET *tool;
	class _TOOLSET
	{
	public:
		~_TOOLSET()
		{
			if (TOOLSET::tool)
				delete TOOLSET::tool;
		}
	};
	static _TOOLSET _tool;
public:
	static TOOLSET*GetTool()
	{
		if (!tool)
			tool = new TOOLSET;
		return tool;
	}
	bool Times(MyTimer &times);
	//中心点
	void Centre(PointXY &Pos, PointXY WH);
	//单字符转宽字符
	wchar_t *s2ws(const string & s);
	//宽字符转单字符
	char* ws2s(const wstring & ws);
	//开方
	float My_Sqrt(float Number);
	//计算两点的距离
	INT My_Distance(Point2DXY Object1, Point2DXY Object2);
	//计算两点的角度
	double StoA(float x1, float y1, float x2, float y2);
	//计算鼠标在基于屏幕在客户端上的坐标
	void SreenCoordinate(PointXY &Pos);
};


#endif