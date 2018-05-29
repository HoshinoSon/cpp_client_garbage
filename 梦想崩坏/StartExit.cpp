#include "StartExit.h"
#include "Music.h"
#include "ToolSet.h"
#include "StartScene.h"
#define _BGM_KEY 0
#define _SE_KEY 1

void CSTARTEXITGAME::InitObject()
{
	m_State = 1;
	Pos = { 1020,20,1060,60 };
	PosFollowWinRect();
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_ConfigBGMSurface, TEXT("PNG"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Quit1.png"), m_NotState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Quit2.png"), m_PassState);
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//Quit3.png"), m_DownState);
}


bool CSTARTEXITGAME::ObjectInstance(WORD t_type)
{
	if (m_Game->CurScene->first == "Start")
	{
		START *t_StartScene = (START*)m_Game->CurScene->second;
		t_StartScene->ForceBreak();
	}
	return 0;
}

void CSTARTEXITGAME::Paint()
{
	DrawImage();
}