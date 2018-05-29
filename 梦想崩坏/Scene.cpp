#include "Scene.h"


CCONPONENT *GAMESCENE::GetConponent()
{
	return m_Conponent;
}

void GAMESCENE::SetInitKey()
{
	m_InitInstance = false;
}

void GAMESCENE::ForceBreak()
{
	m_ForceBreak = true;
}

PointXY *GAMESCENE::GetCurSorPos()
{
	return &m_CurPos;
}

void GAMESCENE::PressDown(PointXY &t_Pos)
{
	m_PressDown.x = t_Pos.x;
	m_PressDown.y = t_Pos.y;
}

void GAMESCENE::UpCursor()
{
	m_PressDown.x = -1;
	m_PressDown.y = -1;
}

PointXY *GAMESCENE::GetPressDown()
{
	return &m_PressDown;
}

void GAMESCENE::SceneSetCurSorPos()
{
	POINT t_CurPos;
	//获取当前鼠标位置
	GetCursorPos(&t_CurPos);
	RECT rc;
	GetWindowRect(m_Game->var.hWnd, &rc);
	m_CurPos.x = ((float)rc.right - (float)rc.left) / (float)m_Game->var.Width;
	m_CurPos.y = ((float)rc.bottom - (float)rc.top) / (float)m_Game->var.Height;
	m_CurPos.x = (float)((float)t_CurPos.x - (float)rc.left) / m_CurPos.x;
	m_CurPos.y = (float)((float)t_CurPos.y - (float)rc.top) / m_CurPos.y;
}

void GAMESCENE::ConponentPaint()
{
	m_Conponent->PaintIns();
}

void GAMESCENE::ButtomJudge(Point2DXY t_CurPos, WORD t_type)
{
	m_Conponent->JudgeClick(t_CurPos, t_type);
}