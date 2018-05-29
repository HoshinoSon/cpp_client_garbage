#include "StartConfig.h"
#include "Music.h"
#include "ToolSet.h"
#include "StartScene.h"
#define _BGM_KEY 0
#define _SE_KEY 1

void CSTARTCONFIG::InitObject()
{
	m_State = 1;
	Pos = { 700,410,900,470 };
	PosFollowWinRect();
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_ConfigBGMSurface, TEXT("PNG"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start1.png"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start2.png"), m_PassState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start3.png"), m_DownState);
}


bool CSTARTCONFIG::ObjectInstance(WORD t_type)
{
	/*STARTCONFIGSCENE *t_Config = STARTCONFIGSCENE::GetInstance();
	t_Config->SetState(true);*/
	if (m_Game->CurScene->first == "Start")
	{
		START *t_StartScene = (START*)m_Game->CurScene->second;
		t_StartScene->SetBGPos(533, 300);
	}
	return 0;
}

void CSTARTCONFIG::Paint()
{
	DrawImage();
}

bool CSTARTCONFIG::Destory()
{
	return 0;
}

void CSTARTCONFIG::ResetPos()
{

}

RECT CSTARTCONFIG::GetPos()
{
	return Pos;
}