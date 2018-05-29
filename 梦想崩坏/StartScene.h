#pragma once
#ifndef _START_SCENE_
#define _START_SCENE_
#include "Scene.h"
#include "Gif.h"


class START : public GAMESCENE
{
private:
	CONPONENTBUTTOM *m_PrimaryConponent;
	PointXY m_Excursion,m_Increment,m_Goal;
	bool m_BGMoveKey;
	GIFIMAGE *Gif;
	Point2D *m_BM;
	Point2D *m_DarkFog;
	float m_DarkDegree;

	/*MUSIC *music;*/
	INT m_Translation;
	INT m_CurKey;
	FLOAT BG_Angle;
	MyTimer m_FollowT;
	bool m_RoleChooseKey, m_ProceedKey, m_ConfigKey, m_AboutKey;
	//Point2D *NewGame[2];
	//Point2D *Quit[2];
	~START()
	{
	}
	void FollowUP();
public:
	//void SetRoleChooseState(bool t_key);
	void Collision(Point2DXY, Point2DXY);
	void MyPaint();
	BOOL InitScene();
	int InitButtom();
	BOOL Run();
	void End();
	//设置背景的位置, x最小-533  最大533, y最小-300  最大300
	void SetBGPos(int x, int y);
	Point2DXY GetBGpos();
};

#endif