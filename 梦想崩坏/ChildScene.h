#pragma once
#ifndef _CHILDSCENE_
#define _CHILDSCENE_
#include "Scene.h"

class CCHILDSCENE
{
protected:
	CONPONENTBUTTOM *m_PrimaryConponent;
	Point2D *m_BackImage;
	GAMES *m_Game;
	INT m_State;
	INT m_IsStart;
public:
	CCHILDSCENE();
	~CCHILDSCENE()
	{
	}
	virtual void SetState(INT ins)
	{
		if (!ins)
			m_PrimaryConponent->SetState(false);
		else
			m_PrimaryConponent->SetState(true);
		m_State = ins;
	}
	virtual INT GetState()
	{
		return m_State;
	}
	virtual CONPONENTBUTTOM *GetConponentInstance()
	{
		return m_PrimaryConponent;
	};
	virtual void Paint()
	{
		RECT rc = { 0,0,m_Game->var.Width,m_Game->var.Height };
		m_Game->var.MTS->D2DDRAW(NULL, TRUE, NULL, m_BackImage, rc, NULL);
	};
	virtual BOOL InitScene() = 0;
	virtual BOOL RunInstance() = 0;
	virtual void StarRun() {};
	virtual void StopRun() {};
};


#endif