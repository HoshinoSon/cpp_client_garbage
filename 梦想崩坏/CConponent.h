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
	//线性的对组件进行运行,可以模拟层次
	list<char *>m_ListButtom;
	std::map<char *, CONPONENTBUTTOM *>m_Buttom;
	std::map<char *, CONPONENTBUTTOM *>::iterator m_FindButtom;
	//子场景
	list<char *>m_ListScene;
	std::map<char *, CCHILDSCENE *>m_Scene;
	std::map<char *, CCHILDSCENE *>::iterator m_FindScene;
public :
	void DelActivateButtom(char *t_cname);
	//加入新组件 t_name:组件名    t_ins:组件实例
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
	//---------------------------------公共---------------------------------------
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