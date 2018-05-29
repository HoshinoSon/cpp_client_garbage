#include "Buttom.h"
#include "Music.h"
#include "Scene.h"
//#include "StartConfigScene.h"


BOOL CONPONENTBUTTOM::CurPosJudge(Point2DXY t_CurPos, WORD t_type)
{
	m_Find = m_Conponent.begin();
	for (; m_Find != m_Conponent.end(); m_Find++)
	{
		if (m_Find->second->CurJudge(*t_CurPos))
			break;
	}
	if (m_Find == m_Conponent.end() || !m_Find->second->GetState())
		return false;

	if (m_Find->second->ObjectInstance(t_type) == RETURNPREVIOUS)
		return RETURNPREVIOUS;
	return true;
}

bool CONPONENTBUTTOM::SetComponent(char *t_buttomname, BASEBUTTOM *buttominstance)
{
	m_Find = m_Conponent.find(t_buttomname);
	if (m_Find == m_Conponent.end())
	{
		m_ListFind.push_back(t_buttomname);
		m_Conponent[t_buttomname] = buttominstance;
	}
	return true;
}

void CONPONENTBUTTOM::SetState(int t_State)
{
	m_State = t_State;
}

INT CONPONENTBUTTOM::GetState()
{
	return m_State;
}



BASEBUTTOM* CONPONENTBUTTOM::Find(char *t_buttomname)
{
	return m_Conponent.find(t_buttomname)->second;
}

void CONPONENTBUTTOM::Paint()
{
	std::vector<char *>::iterator t_ListFind = m_ListFind.begin();
	for (int i = 0; i < m_Conponent.size(); i++)
	{
		m_Find = m_Conponent.find(*t_ListFind);
		if(m_Find->second->GetState())
			m_Find->second->Paint();
		t_ListFind++;
	}
}

void CONPONENTBUTTOM::Destory()
{
	m_Conponent.clear();
}

BASEBUTTOM::BASEBUTTOM()
{
	m_Angle = 0;
	m_Opacity = 1;
	m_Game = GAMES::GetInstance();
	m_Tool = TOOLSET::GetTool();
}

void BASEBUTTOM::DrawImage()
{
	m_Game->CurScene->second;
	PointXY *t_CurSorPos = m_Game->CurScene->second->GetCurSorPos();
	RECT rc;
	GetWindowRect(m_Game->var.hWnd, &rc);

	if (t_CurSorPos->x > Pos.left && t_CurSorPos->x < Pos.right &&
		t_CurSorPos->y > Pos.top && t_CurSorPos->y < Pos.bottom)
	{
		if (m_Game->CurScene->second->GetPressDown()->x > Pos.left &&
			m_Game->CurScene->second->GetPressDown()->x < Pos.right &&
			m_Game->CurScene->second->GetPressDown()->y > Pos.top &&
			m_Game->CurScene->second->GetPressDown()->y < Pos.bottom)
			m_Game->var.MTS->D2DDRAW(m_Angle, m_Opacity, &rc, m_DownState, Pos, NULL);
		else
			m_Game->var.MTS->D2DDRAW(m_Angle, m_Opacity, &rc, m_PassState, Pos, NULL);
	}
	else
	{
		m_Game->var.MTS->D2DDRAW(m_Angle, m_Opacity, &rc, m_NotState, Pos, NULL);
	}
}

void CONPONENTBUTTOM::CloseConponent()
{
	m_Find = m_Conponent.begin();
	for (; m_Find != m_Conponent.end(); m_Find++)
	{
		m_Find->second->SetState(FALSE);
	}
}

void CONPONENTBUTTOM::OpenConponent()
{
	m_Find = m_Conponent.begin();
	for (; m_Find != m_Conponent.end(); m_Find++)
	{
		m_Find->second->SetState(TRUE);
	}
}

//----------------------------------------------------------------------------
//                           Map
//Cope: 2017/3/18/0.15
//WriteAuthor: 范洋
//State:暂时废弃,获取新方法
//----------------------------------------------------------------------------

//void MyMap::SetConponent(CHAR *t_name, CONPONENT* t_conponent)
//{
//	m_NameFind = find(m_Name.begin(),m_Name.end(),t_name);
//	if (m_NameFind != m_Name.end())
//		return;
//	m_Name.push_back(t_name);
//	m_Conponent.push_back(t_conponent);
//	m_Size++;
//}
//
//CONPONENT *MyMap::Find(CHAR *t_name)
//{
//	int Pos = 0;
//	m_NameFind = m_Name.begin();
//	for (int i = 0; i < m_Name.size(); i++)
//	{
//		if (strcmp(t_name, *m_NameFind) == 0)
//		{
//			m_InsFind = m_Conponent.begin();
//			m_InsFind += i;
//			return *m_InsFind;
//		}
//		m_NameFind++;
//	}
//}
//
//int MyMap::Size()
//{
//	return m_Size;
//}
bool BASEBUTTOM::CurJudge(PointXY &t_CurPos)
{
	if (!m_State)
		return false;
	if (t_CurPos.x > Pos.left && t_CurPos.x < Pos.right &&
		t_CurPos.y > Pos.top && t_CurPos.y < Pos.bottom)
		return true;
	return false;
}
void BASEBUTTOM::PosFollowWinRect()
{
	Pos.left = (LONG)(Pos.left / ((float)WINWIDTH / (float)m_Game->var.Width));
	Pos.right = (LONG)(Pos.right / ((float)WINWIDTH / (float)m_Game->var.Width));
	Pos.top = (LONG)(Pos.top / ((float)WINHEIGHT / (float)m_Game->var.Height));
	Pos.bottom = (LONG)(Pos.bottom / ((float)WINHEIGHT / (float)m_Game->var.Height));
}


RECT BASEBUTTOM::GetPos()
{
	return this->Pos;
}

bool BASEBUTTOM::Destory()
{
	DSTORYOBJ(m_NotState)
	DSTORYOBJ(m_DownState)
	DSTORYOBJ(m_PassState)
	return true;
}