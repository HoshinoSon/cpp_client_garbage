#include "ChooseRoleReturn.h"
#include "Music.h"
#include "ToolSet.h"
#include "StartScene.h"
#define _BGM_KEY 0
#define _SE_KEY 1

void CCHOOSEROLERETURN::InitObject()
{
	m_State = 1;
	Pos = { 20,20,80,50 };
	PosFollowWinRect();
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_ConfigBGMSurface, TEXT("PNG"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Return1.png"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Return2.png"), m_PassState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Return3.png"), m_DownState);
}


bool CCHOOSEROLERETURN::ObjectInstance(WORD t_type)
{
	/*STARTCONFIGSCENE *t_Config = STARTCONFIGSCENE::GetInstance();
	t_Config->SetState(true);*/
	if (m_Game->CurScene->first == "Start")
	{
		START *t_StartScene = (START*)m_Game->CurScene->second;
		//t_StartScene->GetConponent()->GetAppointButtom("ChooseRole")->CloseConponent();
		//t_StartScene->GetConponent()->GetAppointButtom("Start")->SetState(true);
		t_StartScene->GetConponent()->GetAppointScene("ChooseRole")->SetState(false);
		t_StartScene->GetConponent()->GetAppointScene("ChooseRole")->StopRun();
		t_StartScene->SetBGPos(0, 0);
	}
	return 0;
}

void CCHOOSEROLERETURN::Paint()
{
	DrawImage();
}

bool CCHOOSEROLERETURN::Destory()
{
	return 0;
}

void CCHOOSEROLERETURN::ResetPos()
{

}

RECT CCHOOSEROLERETURN::GetPos()
{
	return Pos;
}