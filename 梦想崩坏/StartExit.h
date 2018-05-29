#pragma once
#ifndef _EXITGAME_
#define _EXITGAME_
#include "Buttom.h"
class CSTARTEXITGAME : public BASEBUTTOM
{
private:
	float m_StripLenth;
public:
	CSTARTEXITGAME()
	{
		InitObject();
	}
	void InitObject();
	void Paint();
	bool ObjectInstance(WORD t_type);
};

#endif