#pragma once
#ifndef _CONPONENT_
#define _CONPONENT_
#include "GameEntry.h"
#define RETURNPREVIOUS -1
class GAMES;

class BASEBUTTOM
{
protected:
	GAMES *m_Game;      //��Ϸ�����
	RECT Pos;			//�������λ��
	Point2D *m_NotState;        //��״̬
	Point2D *m_PassState;       //��꾭��
	Point2D *m_DownState;		//��갴��
	TOOLSET *m_Tool;            //���߿�
	bool m_State;               //���״̬ true����,false�ر�
	float m_Angle;				//�����ת�Ƕ�
	float m_Opacity;			//���͸����
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
	//���á��������,1 : �����(����������) 2: ���ʵ��   
	bool SetComponent(char* t_conponentname, BASEBUTTOM*conponentinstance);
	//��ȡ�����ı��
	INT GetState();
	//��������ı��
	void SetState(int t_state);
	//������� 1: �����
	BASEBUTTOM* Find(char *t_conponentname);
	//��������е���ж�
	BOOL CurPosJudge(Point2DXY t_CurPos, WORD t_type);
	//�������ͼ��
	void Paint();
	//���������
	void Destory();
	//�ر��������
	void CloseConponent();
	//���������
	void OpenConponent();
};

#endif