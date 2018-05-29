#include "RoleChooseScene.h"
#include "ChooseRoleReturn.h"

BOOL ROLECHOOSE::InitScene()
{
	m_Game = GAMES::GetInstance();
	m_PrimaryConponent = new CONPONENTBUTTOM;
	ROLEATT *t_Role = new ROLEATT;
	Point2D *t_RoleImage;
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//HouxinoUmoe.png"), t_RoleImage);
	*t_Role = { "Houxinou",true,t_RoleImage };
	m_Role.push_back(t_Role);
	t_Role = new ROLEATT;
	m_Game->var.MTS->MyLoadImage(TEXT("Textrue//Start//SayukiAsumi.png"), t_RoleImage);
	*t_Role = { "SayukiAsumi",false,t_RoleImage };
	m_Role.push_back(t_Role);

	m_FindRole = m_Role.begin();

	CCHOOSEROLERETURN *t_Return = new CCHOOSEROLERETURN;
	m_PrimaryConponent->SetComponent("Return", t_Return);

	QuitRole = NULL;
	m_TranslationKey = true;
	time.Pre = (float)clock();
	time.Interval = 200;
	m_Translation = 0;
	m_Transparency = 0;
	m_Change = 1;
	return TRUE;
}

BOOL ROLECHOOSE::RunInstance()
{
	if(m_Game->CurScene->second->GetBGpos()->x > 480 && !m_IsStart)
		this->StarRun();
	if (!m_IsStart)
		return false;

	if (m_TranslationKey)
	{
		if (m_Transparency < 1)
			m_Transparency += 0.012f;
		if(m_Translation < 250)
			m_Translation+=3;
		if (m_Translation >= 250)
			m_TranslationKey = false;
	}
	RECT rc;
	GetWindowRect(m_Game->var.hWnd, &rc);
	TOOLSET *t_T = TOOLSET::GetTool();
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (t_T->Times(time))
		{
			QuitRole = *m_FindRole;
			m_FindRole++;
			if (m_FindRole == m_Role.end())
				m_FindRole = m_Role.begin();
			m_TranslationKey = true;
			m_Translation = 0;
			m_Transparency = 0;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (t_T->Times(time))
		{
			QuitRole = *m_FindRole;
			if (m_FindRole == m_Role.begin())
				m_FindRole = m_Role.end();
			m_FindRole--;
			m_Transparency = 0;
			m_TranslationKey = true;
			m_Translation = 0;
		
		}
	}
	if (GetAsyncKeyState(VK_RETURN) & 1)
	{

	}

	return TRUE;
}

void ROLECHOOSE::Paint()
{
	if (!m_IsStart)
		return;
	//BG_Angle += 0.01;
	RECT rc;
	rc = { 450,50,950,550 };
	
	//第一层
	RECT t_Drc = { 450 + (LONG)m_Translation ,50,950 + (LONG)m_Translation,550 };
	if(QuitRole)
		m_Game->var.MTS->D2DDRAW(NULL, 1 - m_Transparency, NULL, QuitRole->m_Image, t_Drc, NULL);
	t_Drc = { 450 + 250 - (LONG)m_Translation ,50,950 + 250 - (LONG)m_Translation,550 };
	m_Game->var.MTS->D2DDRAW(NULL, m_Transparency, NULL, (*m_FindRole)->m_Image, t_Drc, NULL);
	/*if (m_Music->GetMusicRoomState() == OPENMUSICROOM)
	m_Music->Paint();*/

	//第二层
	//m_Game->var.MTS->D2DDRAW(BG_Angle, TRUE, NULL, Frame[1], rc);
	//ConponentPaint();

	//第三层
	//m_Game->var.MTS->D2DDRAW(BG_Angle, TRUE, NULL, Frame[2], rc);

	//if (m_Config->GetState() == CONFIGSCENEOPEN)
	//{
	//	m_Config->Paint();
	//}

	//for (int i = 0; i < 5; i++)
	//{
	//	if (m_CurKey == i)
	//	{
	//		if (m_Translation < 10)
	//			m_Translation++;
	//		m_Key_Down[i].Pos.left -= m_Translation;
	//		m_Key_Down[i].Pos.right -= m_Translation;
	//		m_Game->var.MTS->D2DDRAW(0, m_Key_Down[i].Image, m_Key_Down[i].Pos);
	//		m_Key_Down[i].Pos.left += m_Translation;
	//		m_Key_Down[i].Pos.right += m_Translation;
	//	}
	//	else
	//	{
	//		m_Game->var.MTS->D2DDRAW(0, m_Key_Up[i].Image, m_Key_Up[i].Pos);
	//	}
	//}
	//RECT gensokyo_rc = { 150,50,650,300 };
	//m_Game->var.MTS->D2DDRAW(0, m_Gensokyo, gensokyo_rc);
}


CONPONENTBUTTOM *ROLECHOOSE::GetConponentInstance()
{
	return m_PrimaryConponent;
}

void ROLECHOOSE::StarRun()
{
	QuitRole = NULL;
	m_FindRole = m_Role.begin();
	m_Transparency = 0;
	m_TranslationKey = true;
	m_Translation = 0;
	m_PrimaryConponent->OpenConponent();
	m_IsStart = true;
}

void ROLECHOOSE::StopRun()
{
	m_PrimaryConponent->CloseConponent();
	m_IsStart = false;
}