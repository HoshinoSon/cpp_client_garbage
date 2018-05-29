#pragma once
#ifndef _GIF_
#define _GIF_
using namespace std;
class GAMES;
class GIFIMAGE
{
private:
	RECT m_rc;
	MyTimer g_Time;
	float m_Angle;
	GAMES *m_Game;
	TOOLSET *m_Tool;
	vector<Point2D *>m_Gif;
	vector<Point2D *>::iterator m_Find;
public:
	void SetGif(RECT &t_rc, float t_angle, int t_time);
	void LoadGifImage(WCHAR *t_fileway, RECT &t_rc);
	void Paint();

};

#endif