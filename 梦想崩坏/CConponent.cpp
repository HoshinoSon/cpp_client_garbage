#include "CConponent.h"

void CCONPONENT::DelActivateButtom(char *t_cname)
{
	list<char*>::iterator t_find = m_ListButtom.begin();
	for (int i = 0; (i < m_ListButtom.size()); i++, t_find++)
	{
		if (*t_find == t_cname)
			break;
	}
	m_ListButtom.erase(t_find);
}
void CCONPONENT::AddConponent(char *t_cname, CONPONENTBUTTOM *t_ins)
{
	m_Buttom[t_cname] = t_ins;
	m_ListButtom.push_front(t_cname);
}

void CCONPONENT::AddConponent(char *t_cname, CCHILDSCENE *t_ins)
{
	m_Scene[t_cname] = t_ins;
	m_ListScene.push_front(t_cname);
}

CPNFINDBUTTOM CCONPONENT::GetButtom()
{
	return m_Buttom.begin();
}

CPNFINDSCENE CCONPONENT::GetScene()
{
	return m_Scene.begin();
}

void CCONPONENT::Find(char *str_t, CONPONENTBUTTOM *t_cButtom)
{
	t_cButtom = m_Buttom.find(str_t)->second;
}

CONPONENTBUTTOM *CCONPONENT::GetAppointButtom(char *t_cname)
{
	return m_Buttom.find(t_cname)->second;
}

void CCONPONENT::Find(char *str_t, CCHILDSCENE *t_cButtom)
{
	t_cButtom = m_Scene.find(str_t)->second;
}

CCHILDSCENE *CCONPONENT::GetAppointScene(char *t_cname)
{
	return m_Scene.find(t_cname)->second;
}

void CCONPONENT::PaintIns()
{
	list<char *>::iterator t_ListFind = m_ListButtom.begin();
	for (int i = 0; i < m_Buttom.size(); i++, t_ListFind++)
	{
		m_FindButtom = m_Buttom.find(*t_ListFind);
		if (m_FindButtom->second->GetState())
			m_FindButtom->second->Paint();
	}
	t_ListFind = m_ListScene.begin();
	for (int i = 0; i < m_Scene.size(); i++)
	{
		m_FindScene = m_Scene.find(*t_ListFind);
		if (m_FindScene->second->GetState())
			m_FindScene->second->Paint();
	}
}

void CCONPONENT::JudgeClick(Point2DXY t_Pos, int type)
{
	list<char *>::iterator t_ListFind = m_ListButtom.begin();
	for (int i = 0; i < m_Buttom.size(); i++, t_ListFind++)
	{
		m_FindButtom = m_Buttom.find(*t_ListFind);
		if (m_FindButtom->second->GetState())
			m_FindButtom->second->CurPosJudge(t_Pos, type);
	}
}

void CCONPONENT::RunConponent()
{
	list<char *>::iterator t_ListFind = m_ListScene.begin();
	for (int i = 0; i < m_Scene.size(); i++)
	{
		m_FindScene = m_Scene.find(*t_ListFind);
		if (m_FindScene->second->GetState())
			m_FindScene->second->RunInstance();
	}
}