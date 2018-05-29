#pragma once
#ifndef _BEGINGAME_
#define _BEGINGAME_
#include "Buttom.h"
class CSTARTBEGINGAME : public BASEBUTTOM
{
private:
	float m_StripLenth;
public:
	CSTARTBEGINGAME()
	{
		InitObject();
	}
	void InitObject();
	void Paint();
	bool ObjectInstance(WORD t_type);
	RECT GetPos();
	bool Destory();
	void ResetPos();
};

#endif