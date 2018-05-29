#pragma once
#ifndef _STARTABOUT_
#define _STARTABOUT_
#include "Buttom.h"
class CSTARTABOUT : public BASEBUTTOM
{
private:
	float m_StripLenth;
public:
	CSTARTABOUT()
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