#include "StartScene.h"
#include "BeginGame.h"
#include "ProceedGame.h"
#include "StartConfig.h"
#include "StartAbout.h"
#include "StartExit.h"
#include <math.h>
#include "RoleChooseScene.h"

BOOL START::InitScene()
{
	if (m_InitInstance <= 0)
	{
		m_AboutKey = m_ConfigKey = m_ProceedKey = m_RoleChooseKey = false;
		m_InitInstance = true;
		m_BGMoveKey = false;
		m_DarkDegree = 0;
		m_Game = GAMES::GetInstance();

		

		m_Conponent = new CCONPONENT;
		//m_Music = MUSIC::GetInstance();
		Gif = new GIFIMAGE;


		InitButtom();

		RECT rc = { 300,200,400,300 };

		POINT t_CurPos;
		GetCursorPos(&t_CurPos);
		m_CurPos.x = (float)t_CurPos.x;
		m_CurPos.y = (float)t_CurPos.y;
		m_Goal.x = m_Increment.x = m_Excursion.x = 0;
		m_Goal.y = m_Increment.y = m_Excursion.y = 0;
		m_FollowT.Pre = (float)clock();
		m_FollowT.Interval = 2;
		//Gif->LoadGifImage(TEXT("UI//StartScene//sss"), rc);
		m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//BM.png"), m_BM);
		m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//DarkFog.png"), m_DarkFog);
	
		m_Tool = TOOLSET::GetTool();
		BG_Angle = 0;
		m_Translation = 0;
		m_Select_p = 1;
		m_CurKey = 0;
		m_Time.Pre = (float)clock();
		m_Time.Interval = 16;
	/*	m_Bg_music.Start_FileName = "土著神の顶点　~Native Faith - Like a rabbit";
		m_Music->LoadLoopMusic(m_Bg_music.Start_FileName, "Music//土著神の顶点　~Native Faith - Like a rabbit.mp3", false);
		m_Music->AddMusic(m_Tool->s2ws("土著神の顶点　~Native Faith - Like a rabbit"));

		m_Music->LoadLoopMusic("メイドと血の懐中时计", "Music//メイドと血の懐中时计.mp3", false);
		m_Music->AddMusic(m_Tool->s2ws("メイドと血の懐中时计"));*/
	}
	//m_Music->SetLoopVolume(150);
	m_ForceBreak = 0;
	//m_Music->PlayLoopMusic(m_Bg_music.Start_FileName);
	return TRUE;
}

int START::InitButtom()
{
	ROLECHOOSE *m_RoleChoose;
	m_RoleChoose = new ROLECHOOSE;
	m_RoleChoose->InitScene();
	m_Conponent->AddConponent("ChooseRole", m_RoleChoose);
	//给场景底层设置组件

	m_PrimaryConponent = new CONPONENTBUTTOM;
	m_PrimaryConponent->SetState(true);
	m_Conponent->AddConponent("Start", m_PrimaryConponent);

	CONPONENTBUTTOM *SceneInstance;
	SceneInstance = m_RoleChoose->GetConponentInstance();
	SceneInstance->SetState(false);
	m_Conponent->AddConponent("ChooseRole", SceneInstance);


	//*******************************************************************
	CSTARTBEGINGAME *t_Begin = new CSTARTBEGINGAME;
	m_PrimaryConponent->SetComponent("Begin", t_Begin);

	CSTARTPROCEEDGAME *t_Proceed = new CSTARTPROCEEDGAME;
	m_PrimaryConponent->SetComponent("Proceed", t_Proceed);

	CSTARTCONFIG *t_Config = new CSTARTCONFIG;
	m_PrimaryConponent->SetComponent("Config", t_Config);

	CSTARTABOUT *t_About = new CSTARTABOUT;
	m_PrimaryConponent->SetComponent("About", t_About);

	CSTARTEXITGAME *t_Exit = new CSTARTEXITGAME;
	m_PrimaryConponent->SetComponent("Exit", t_Exit);
	//*******************************************************************
	return true;
}


BOOL START::Run()
{
	MyTimer time;

	time.Pre = (float)clock();
	time.Interval = 100;
	RECT rc;
	GetWindowRect(m_Game->var.hWnd, &rc);
	//m_Game->var.AM.PlayLoopAudio(m_Bg_music.Start_FileName);
	MSG msg;
	GetMessage(&msg, NULL, NULL, NULL);
	// 主消息循环: 
	while (msg.message != WM_QUIT)
	{

		FollowUP();
		SceneSetCurSorPos();
		time.Cur = (float)clock();
		if (m_Excursion.x > -100 && m_Excursion.x < 100 && m_Excursion.y > -100 && m_Excursion.y < 100)
			m_PrimaryConponent->SetState(true);
		else
			m_PrimaryConponent->SetState(false);
		m_Conponent->RunConponent();
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (m_CurKey > 0 && time.Cur - time.Pre > time.Interval)
			{
				m_Translation = 0;
				m_CurKey--;
				m_Select_p--;
				time.Pre = (float)clock();
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (m_CurKey < 4 && time.Cur - time.Pre > time.Interval)
			{
				m_Translation = 0;
				m_CurKey++;
				m_Select_p++;
				time.Pre = (float)clock();
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			/*if (m_Select_p == CONFIG_SCENE)
			{
				CONPONENT *t_CPInstance;
				t_CPInstance = m_CPNInstance->Find(START_CONFIG);
				if (t_CPInstance->ObjectInstance(1) == RETURNPREVIOUS)
				{
					break;
				}
				m_Music->PlayLoopMusic(m_Bg_music.Start_FileName);
			}*/
		}
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		if (m_ForceBreak)
		{
			if (m_Game->CurScene->first != "Start")
				return true;
			else
			{
				End();
				return false;
			}
		}
		if (m_Tool->Times(m_Time))
			InvalidateRect(m_Game->var.hWnd, 0, false);
	}
	return TRUE;
}

void START::MyPaint()
{
	//BG_Angle += 0.01;
	if (m_ForceBreak)
		return;
	RECT rc;
	rc = { NULL - 533 + (LONG)m_Excursion.x,
		NULL - 300 + (LONG)m_Excursion.y,
		m_Game->var.Width + 533 + (LONG)m_Excursion.x,
		m_Game->var.Height + 300 + (LONG)m_Excursion.y
	};
	//第一层
	m_Game->var.MTS->D2DDRAW(BG_Angle, TRUE, NULL, m_BM, rc, NULL);
	rc = { 0,0,1066,600 };
	m_Game->var.MTS->D2DDRAW(NULL, m_DarkDegree, NULL, m_DarkFog,rc, NULL);
	//第二层
	m_Conponent->PaintIns();
	//第三层

}

void START::Collision(Point2DXY, Point2DXY)
{

}

void START::End()
{
	if (m_ForceBreak)
		return;
	if (m_Select_p)
	{
		m_Game->CurScene = m_Game->Scene.find("Rinkayi");
	}
}

void START::SetBGPos(int x, int y)
{
	m_DarkDegree = 0;
	float t_X = x - m_Excursion.x, t_Y = y - m_Excursion.y;
	float t_VK = m_Tool->My_Sqrt(t_X * t_X + t_Y * t_Y);
	m_Increment.x = t_X / t_VK * 3;
	m_Increment.y = t_Y / t_VK * 3;
	m_Goal.x = (float)x;
	m_Goal.y = (float)y;
	m_FollowT.Interval = 0.1f;
	m_BGMoveKey = true;
}

Point2DXY START::GetBGpos()
{
	return &m_Excursion;
}

void START::FollowUP()
{
	if (!m_Tool->Times(m_FollowT))
		return;
	if (!m_BGMoveKey)
		return;
	if (m_FollowT.Interval < 12)
		m_FollowT.Interval += m_FollowT.Interval * 0.0235f;
	/*	((((m_Goal.x < 0 ? m_Goal.x * -1 : m_Goal.x)
			- (m_Excursion.x < 0 ? m_Excursion.x * -1 :
			(m_Excursion.x == 0 ? m_Excursion.x + 1 : m_Excursion.x))) 
			+ (((m_Goal.y < 0 ? m_Goal.y * -1 : m_Goal.y)
			- (m_Excursion.y < 0 ? m_Excursion.y * -1 :
			(m_Excursion.y == 0 ? m_Excursion.y + 1 : m_Excursion.y)))) / 2) / 5) / 100;*/
	if (m_DarkDegree < 0.5 && m_Goal.x)
		m_DarkDegree += 0.0020000f;
	if (m_Goal.x > m_Excursion.x)
	{
		m_Excursion.x += m_Increment.x < 0 ? m_Increment.x * -1 : m_Increment.x;
		if (m_Goal.x < m_Excursion.x)
			m_BGMoveKey = false;
	}
	if (m_Goal.x < m_Excursion.x)
	{
		m_Excursion.x -= m_Increment.x < 0 ? m_Increment.x * -1 : m_Increment.x;
		if (m_Goal.x > m_Excursion.x)
			m_BGMoveKey = false;
	}
	if (m_Goal.y > m_Excursion.y)
	{
		m_Excursion.y += m_Increment.y < 0 ? m_Increment.y * -1: m_Increment.y;
		if (m_Goal.y < m_Excursion.y)
			m_BGMoveKey = false;
	} 
	if (m_Goal.y < m_Excursion.y)
	{
		m_Excursion.y -= m_Increment.y < 0 ? m_Increment.y * -1 : m_Increment.y;
		if (m_Goal.y > m_Excursion.y)
			m_BGMoveKey = false;
	}
	//if (m_Increment.x > m_Excursion.x)
	//	m_Excursion.x += 
	/*	  ((m_Increment.x < 0 ? m_Increment.x * -1:m_Increment.x)
		/ (m_Excursion.y < 0 ? m_Excursion.y * -1 : (m_Excursion.y == 0 ? m_Excursion.y + 1 : m_Excursion.y)))
		/ 100;
*/
	//if (m_Increment.x < m_Excursion.x)
	//	m_Excursion.x -=
	//		(m_Increment.x < 0 ? m_Increment.x * -1 : m_Increment.x
	//			/ m_Excursion.y < 0 ? m_Excursion.y * -1 : m_Excursion.y == 0 ? m_Excursion.y + 1 : m_Excursion.y) / 100;

	//if (m_Increment.y > m_Excursion.y)
	//	m_Excursion.y +=
	//		((m_Increment.y < 0 ? m_Increment.y * -1 : m_Increment.y)
	//		/ (m_Excursion.y < 0 ? m_Excursion.y * -1 : m_Excursion.y == 0? m_Excursion.y + 1: m_Excursion.y)) / 100;

	//if (m_Increment.y < m_Excursion.y)
	//	m_Excursion.y -=
	//		(m_Increment.y < 0 ? m_Increment.y * -1 : m_Increment.y
	//			/ m_Excursion.y < 0 ? m_Excursion.y * -1 : m_Excursion.y == 0 ? m_Excursion.y + 1 : m_Excursion.y) / 100;

}

//void START::SetRoleChooseState(bool t_key)
//{
//	m_RoleChoose->GetConponentInstance()->SetState(true);
//	m_RoleChooseKey = t_key;
//}