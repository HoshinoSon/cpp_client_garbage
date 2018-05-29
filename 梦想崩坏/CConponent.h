#pragma once
#ifndef _CCONPONENT_
#define _CCONPONENT_
#include <map>
#include <vector>
#include <list>
#include "Buttom.h"
#include "ChildScene.h"
#define CPNFINDBUTTOM std::map<char *, CONPONENTBUTTOM *>::iterator
#define CPNFINDSCENE std::map<char *,CCHILDSCENE *>::iterator
using namespace std;
class CCHILDSCENE;

class CCONPONENT
{
	//���ԵĶ������������,����ģ����
	list<char *>m_ListButtom;
	std::map<char *, CONPONENTBUTTOM *>m_Buttom;
	std::map<char *, CONPONENTBUTTOM *>::iterator m_FindButtom;
	//�ӳ���
	list<char *>m_ListScene;
	std::map<char *, CCHILDSCENE *>m_Scene;
	std::map<char *, CCHILDSCENE *>::iterator m_FindScene;
public :
	void DelActivateButtom(char *t_cname);
	//��������� t_name:�����    t_ins:���ʵ��
	void AddConponent(char *t_cname, CONPONENTBUTTOM *t_ins);
	void AddConponent(char *t_cname, CCHILDSCENE *t_ins);
	CPNFINDBUTTOM GetButtom();
	CPNFINDSCENE GetScene();
	//--------------------------------BUTTOM---------------------------------------
	void Find(char *str_t, CONPONENTBUTTOM *t_cButtom);

	CONPONENTBUTTOM *GetAppointButtom(char *t_cname);
	//---------------------------------SCENE--------------------------------------
	void Find(char *str_t, CCHILDSCENE *t_cButtom);

	CCHILDSCENE *GetAppointScene(char *t_cname);
	//---------------------------------����---------------------------------------
	void PaintIns();
	void JudgeClick(Point2DXY t_Pos, int type);
	void RunConponent();
	std::map<char *, CONPONENTBUTTOM *> & operator =(std::map<char *, CONPONENTBUTTOM *> &)
	{
		return m_Buttom;
	}
	void operator [](char *str_t)
	{

	}
};

#endif