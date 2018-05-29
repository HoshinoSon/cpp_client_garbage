#include "BeginGame.h"
#include "Music.h"
#include "ToolSet.h"
#include "StartScene.h"
#define _BGM_KEY 0
#define _SE_KEY 1

void CSTARTBEGINGAME::InitObject()
{
	m_State = 1;
	Pos = { 700,250,900,310 };
	PosFollowWinRect();
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_ConfigBGMSurface, TEXT("PNG"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start1.png"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start2.png"), m_PassState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start3.png"), m_DownState);
}


bool CSTARTBEGINGAME::ObjectInstance(WORD t_type)
{
	/*STARTCONFIGSCENE *t_Config = STARTCONFIGSCENE::GetInstance();
	t_Config->SetState(true);*/
	if (m_Game->CurScene->first == "Start")
	{
		START *t_StartScene = (START*)m_Game->CurScene->second;
		t_StartScene->SetBGPos(533, -300);
		t_StartScene->GetConponent()->GetAppointScene("ChooseRole")->SetState(true);
		t_StartScene->GetConponent()->GetAppointScene("ChooseRole")->StopRun();
		//t_StartScene->GetConponent()->GetAppointButtom("ChooseRole")->SetState(true);
		//t_StartScene->GetConponent()->GetAppointButtom("ChooseRole")->OpenConponent();
		t_StartScene->GetConponent()->GetAppointButtom("Start")->SetState(false);
	}
	//GAMESCENE *t_Game = m_Game->CurScene->second;
	return 0;
}

void CSTARTBEGINGAME::Paint()
{
	DrawImage();
}

bool CSTARTBEGINGAME::Destory()
{
	return 0;
}

void CSTARTBEGINGAME::ResetPos()
{

}

RECT CSTARTBEGINGAME::GetPos()
{
	return Pos;
}