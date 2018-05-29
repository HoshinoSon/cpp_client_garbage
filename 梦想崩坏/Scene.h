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
	//���µ�λ��
	PointXY m_PressDown;
	//���λ��
	PointXY m_CurPos;
	//�Ƿ��ʼ��
	BOOL m_InitInstance;
	CCONPONENT *m_Conponent;
	//��������
	BG_Music m_Bg_music;
	//��Ļ��
	DMK *m_Dmk;
	//���ֿ�
	MUSIC *m_Music;
	//ǿ���˳�����
	bool m_ForceBreak;
	//
	Point2D *m_TextrueMap[14];
	//ˢ��ʱ��
	MyTimer m_Time;
	//���߿�
	TOOLSET *m_Tool;
	//��ͼ
	vector<MAP>::iterator m_pMap;
	//�����ܽṹ
	GAMES *m_Game;
	//������
	ROLE *m_Role;
	int m_Select_p;
	//FIGURE *Enemy;
	//����
	Point2D *BG;
	//��ǰ����λ��
	INT Cur_O_Pos;
	//��ǰ����λ��
	INT Cur_S_Pos;
public:


	virtual CCONPONENT *GetConponent();
	//��������ʼ��Ϊ0,��ʾδ��ʼ��
	virtual void SetInitKey();
	//����ǰ����ǿ�ƽ���
	virtual void ForceBreak();
	//��ȡ���λ��
	virtual PointXY *GetCurSorPos();
	//��ײ
	virtual void Collision(Point2DXY, Point2DXY) = 0;
	//����
	virtual void MyPaint() = 0;
	//��ʼ��
	virtual BOOL InitScene() = 0;
	virtual int InitButtom() { return true; };
	//���г���
	virtual BOOL Run() = 0;
	//��������
	virtual void End() = 0;
	//��갴��
	virtual void PressDown(PointXY &t_Pos);
	virtual void UpCursor();
	//��ȡ���µ�λ��
	virtual PointXY *GetPressDown();
	//���õ�ǰ���λ��
	virtual void SceneSetCurSorPos();
	//�������
	virtual void ConponentPaint();
	//������ж�
	virtual void ButtomJudge(Point2DXY t_CurPos, WORD t_type);
	//������Ļ���� ע: ����Ϊ����   �����ҪX��+10����   ��ô��д-10 
	virtual void SetBGPos(int x, int y) {};
	//��ȡ��Ļ���� 
	virtual Point2DXY GetBGpos() { return false; };
};

#endif