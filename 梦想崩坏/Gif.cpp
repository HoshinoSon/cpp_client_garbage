
#include "GameEntry.h"
#include "Gif.h"
void GIFIMAGE::SetGif(RECT &t_rc, float t_angle, int t_time)
{
	m_rc.left = t_rc.left;
	m_rc.right = t_rc.right;
	m_rc.top = t_rc.top;
	m_rc.bottom = t_rc.bottom;
	m_Angle = t_angle;
	g_Time.Interval = (float)t_time;
}

void GIFIMAGE::LoadGifImage(WCHAR *t_fileway, RECT &t_rc)
{
	m_rc.left = t_rc.left;
	m_rc.right = t_rc.right;
	m_rc.top = t_rc.top;
	m_rc.bottom = t_rc.bottom;
	m_Angle = 0;
	g_Time.Pre = (float)clock();
	g_Time.Interval = 20;

	m_Game = GAMES::GetInstance();
	m_Tool = TOOLSET::GetTool();
	Point2D *t_Image;
	char arr1[64];
	char arr2[64];
	for (int i = 1; i < 10000; i++)
	{
		memset(arr1, 0, 64);
		memset(arr2, 0, 64);
		strcat(arr1, m_Tool->ws2s(t_fileway));
		strcat(arr1, "//");
		sprintf_s(arr2, "%d", i);
		strcat(arr1, arr2);
		strcat(arr1, ".png");
		bool noimage = (bool *)m_Game->var.MTS->MyLoadImage(m_Tool->s2ws(arr1), t_Image);
		if (!noimage)
			break;
		m_Gif.push_back(t_Image);
	}
	m_Find = m_Gif.begin();
}

void GIFIMAGE::Paint()
{

	if (m_Find == m_Gif.end())
		m_Find = m_Gif.begin();
	RECT rc;
	GetWindowRect(m_Game->var.hWnd, &rc);
	m_Game->var.MTS->D2DDRAW(m_Angle, TRUE, &rc, *m_Find, m_rc, NULL);
	if (m_Tool->Times(g_Time))
		m_Find++;

}