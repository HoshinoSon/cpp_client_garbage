#pragma once
#ifndef TOOL_SET
#define TOOL_SET
#define pi 3.1415926535  
#define SLOPE_ONE 0x01
#define SLOPE_TWO 0x02
#define SLOPE_THREE 0x03
#define KEY_KEEP_DOWN    0 //��������
#define KEY_CURRENT_DOWN 1 //��ǰ����
#define KEY_KEEP_UP      2 //�����ſ�
#define KEY_CURRENT_UP   3 //��ǰ�ſ�
#define MONSTERBULLET 0x01  //���﷢��
#define FIGUREBULLET 0x02   //���﷢��
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
	//˳��ִ��
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

//-------------------------------------------------ֱ�߳�----------------------------------------------

struct STRAIGHT
{
	INT Harm;
	PointXY LocaTion; //��ǰλ��
	PointXY VK;       //����λ��
	FLOAT Angle;        //ͼƬ�Ƕ�
	STC Type;           //�����︽��״̬
	INT WhatIsBullet;   //˭����ģ�
	INT Image;          //ͼƬ
	MyTimer ExecuteType;//ʲôʱ��ʼִ�з�����ĸ���״̬
};

typedef struct DMK_SA_MEMORI
{
	DMK_SA_MEMORI *next;
	DMK_SA_MEMORI *prev;
	STRAIGHT data;
}*pDMK_SA_MEMORI;

typedef pDMK_SA_MEMORI DMKSAMMR;
typedef DMK_SA_MEMORI newDMKSAMMR;



//-------------------------------------------------���߳�------------------------------------------------
struct CURVA
{
	INT Harm;
	pBCN Bezier_node;   //��һ���͵��ĸ�����ʼ���Ŀ���,�ڶ���������Ϊ���Ƶ�
	PointXY ObjectPos;//��ǰλ��
	PointXY VK;       //����λ��
	INT Image;          //ͼƬ
	INT WhatIsBullet;   //˭����ģ�
	STC Type;           //����״̬
	DWORD Run;          //δ֪
	MyTimer ExecuteType;//ʲôʱ��ʼִ�и���״̬
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


	//--------------------------------------------ֱ�����ͺ�������--------------------------------------------
	//Բ��
	void BulletRoundNess(DMKSAMMR &head, CONST Point2D _image, CONST SKILLTYPE _st,
		CONST INT _angle, INT Slope, INT what_is_bullet, PointXY Pos, STC stc, INT image);
	//����
	void BulletSector(DMKSAMMR &head, INT _angle, INT radius, Point2D _image, const SKILLTYPE _st, const MyTimer _times, INT Slope);
	//�ֳ�2��
	void FissionMirroring(DMKSAMMR &head, DMKSAMMR &node, INT angle, Point2D _image, const SKILLTYPE _st, INT Slope);
	//�ֳ�һ��
	void FissionDisperse(size_t size, INT angle, INT Slope);
	//--------------------------------------------------END---------------------------------------------------

	//--------------------------------------------�������ͺ�������--------------------------------------------
	void BezierCurva(Point2DXY &object_pos, const Point2DXY location_state, const Point2DXY location1,
		const Point2DXY location2, const Point2DXY location_goal, INT Slope);
	void BulletRoundNess(CURVA type, INT Slope);					   //Բ��
	void BulletSector(INT angle, INT Slope);						   //����
	void FissionMirroring(DMKCVMMR &head, INT angle, INT Slope);                      //�ֳ�2��
	void FissionDisperse(DMKCVMMR &head, size_t size, INT angle, INT Slope);		   //�ֳ�һ��
																					   //--------------------------------------------------END---------------------------------------------------

																					   //------------------------------------------------��������------------------------------------------------
	DMKCVMMR dmkcvmmr;
	DMKSAMMR dmksammr;

	DMKSAMMR DCMFHead;
	DMKSAMMR DSMMHead;
	//DMKSAMMR *GetSA()

	Point2D *FSkillChartLet[10];
	Point2D *MSkillChartLet[10];
	//--------------------------------------------------END---------------------------------------------------

	//------------------------------------------------��������------------------------------------------------
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

//--------------------------------------------------������----------------------------------------------------

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
	//��ʼ������
	void IniInputMgr(int num, int *pKey);
	//��ⰴ��
	void CheckKeyState();
	//��ȡ������Ϣ
	int MyGetKeyState(int pos);

};

//------------------------------------------------���ߺ�������------------------------------------------------
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
	//���ĵ�
	void Centre(PointXY &Pos, PointXY WH);
	//���ַ�ת���ַ�
	wchar_t *s2ws(const string & s);
	//���ַ�ת���ַ�
	char* ws2s(const wstring & ws);
	//����
	float My_Sqrt(float Number);
	//��������ľ���
	INT My_Distance(Point2DXY Object1, Point2DXY Object2);
	//��������ĽǶ�
	double StoA(float x1, float y1, float x2, float y2);
	//��������ڻ�����Ļ�ڿͻ����ϵ�����
	void SreenCoordinate(PointXY &Pos);
};


#endif