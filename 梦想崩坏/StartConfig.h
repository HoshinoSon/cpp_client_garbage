#pragma once
#ifndef _STARTCONFIG_
#define _STARTCONFIG_
#include "Buttom.h"
class CSTARTCONFIG : public BASEBUTTOM
{
private:
	float m_StripLenth;
public:
	CSTARTCONFIG()
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