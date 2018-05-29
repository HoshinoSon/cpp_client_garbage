#pragma once
#ifndef _STARTPROCEED_
#define _STARTPROCEED_
#include "Buttom.h"
class CSTARTPROCEEDGAME : public BASEBUTTOM
{
private:
	float m_StripLenth;
public:
	CSTARTPROCEEDGAME()
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