#include "StartAbout.h"
#include "Music.h"
#include "ToolSet.h"
#include "StartScene.h"
#define _BGM_KEY 0
#define _SE_KEY 1

void CSTARTABOUT::InitObject()
{
	m_State = 1;
	Pos = { 700,490,900,550 };
	PosFollowWinRect();
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_ConfigBGMSurface, TEXT("PNG"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start1.png"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start2.png"), m_PassState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Start3.png"), m_DownState);
}


bool CSTARTABOUT::ObjectInstance(WORD t_type)
{
	/*STARTCONFIGSCENE *t_Config = STARTCONFIGSCENE::GetInstance();
	t_Config->SetState(true);*/
	if (m_Game->CurScene->first == "Start")
	{
		START *t_StartScene = (START*)m_Game->CurScene->second;
		t_StartScene->SetBGPos(-533, -300);
	}
	return 0;
}

void CSTARTABOUT::Paint()
{
	DrawImage();
}

bool CSTARTABOUT::Destory()
{
	return 0;
}

void CSTARTABOUT::ResetPos()
{

}

RECT CSTARTABOUT::GetPos()
{
	return Pos;
}