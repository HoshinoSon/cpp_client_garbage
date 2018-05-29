#pragma once
#ifndef _ROLECHOOSE_SCENE_
#define _ROLECHOOSE_SCENE_
#include "ChildScene.h"
#include "Gif.h"

struct ROLEATT
{
	char *m_RoleName;
	bool m_OpenKey;
	Point2D *m_Image;
};


class ROLECHOOSE : public CCHILDSCENE
{
private:
	GIFIMAGE *Gif;
	Point2D *m_DarkDegree;
	ROLEATT *QuitRole;
	std::vector<ROLEATT *>m_Role;
	std::vector<ROLEATT *>::iterator m_FindRole;
	bool m_Change;
	MyTimer time;
	/*MUSIC *music;*/
	bool m_TranslationKey;
	FLOAT m_Translation;
	FLOAT m_Transparency;
	INT m_CurKey;
	//Point2D *NewGame[2];
	//Point2D *Quit[2];
	~ROLECHOOSE()
	{
	}
public:
	CONPONENTBUTTOM *GetConponentInstance();
	void Paint();
	BOOL InitScene();
	BOOL RunInstance();
	void StarRun();
	void StopRun();
};

#endif