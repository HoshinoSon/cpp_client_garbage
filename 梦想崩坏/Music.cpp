#include "Scene.h"
//#include "MusicQuit.h"
//#include "MusicMinimize.h"
//#include "MusicStrip.h"
//#include "MusicPlayPos.h"
//#include "MusicPlay.h"

MUSIC *MUSIC::music;

void MUSIC::InitMusic()
{
	m_Game = GAMES::GetInstance();
	tool = TOOLSET::GetTool();
	//m_CPNInstance = new CONPONENTINSTANCE;
	//m_CPNInstance->SetNumber(1);
	m_MusicState = 0;
	m_PlayState = 2;
	m_PlayListing = 2;
	//加载音乐信息
	LoadMusicFile();


	//CMUSICQUIT *t_MusicQuit = new CMUSICQUIT;
	//m_CPNInstance->SetComponent(MUSIC_QUIT, t_MusicQuit);

	//CMUSICMINIMIZE *t_Minimize = new CMUSICMINIMIZE;
	//m_CPNInstance->SetComponent(MUSIC_MINIMIZE, t_Minimize);

	//CMUSICSTRIP *t_Strip = new CMUSICSTRIP;
	//m_CPNInstance->SetComponent(MUSIC_STRIP, t_Strip);

	//CMUSICPLAYPOS *t_Pos = new CMUSICPLAYPOS;
	//m_CPNInstance->SetComponent(MUSIC_POS, t_Pos);

	//CMUSICPLAY *t_Play = new CMUSICPLAY;
	//m_CPNInstance->SetComponent(MUSIC_PLAY, t_Play);

	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_MusicFrame, TEXT("PNG"), m_BackImage);
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_MusicStrip1, TEXT("PNG"), BackStrip[0]);
	//m_Game->var.MTS->MyLoadImageFromResource(IMAGE_MusicStrip2, TEXT("PNG"), BackStrip[1]);
}

DWORD WINAPI MusicRoom(LPVOID lpParam)
{
	GAMES *t_Game = GAMES::GetInstance();
	MUSIC *t_Music = t_Music->GetInstance();
	//t_Time.Pre = clock();
	//t_Time.Interval = t_Music->GetLlenth();
	while (1)
	{
		//t_Music->GetPlayPos();
		t_Music->WhetherNext();
		if (t_Music->GetMusicState() == OPENMUSICROOM)
			break;
	}
	return 0;
}

void MUSIC::MusicMoon()
{
	MyTimer g_time;
	g_time.Pre = (float)clock();
	g_time.Interval = 16;
	MusicKey = BackKey = 0;
	CurPlayUI = MusicGather.begin();
	WhetherNext();
}

void MUSIC::Paint()
{

	//game->var.MTS->BeginDraw();
	RECT rc = { 28,158,1038,572 };
	rc.left = (LONG)(rc.left / (1066.0 / (float)m_Game->var.Width));
	rc.right = (LONG)(rc.right / (1066.0 / (float)m_Game->var.Width));
	rc.top = (LONG)(rc.top / (600.0 / (float)m_Game->var.Height));
	rc.bottom = (LONG)(rc.bottom / (600.0 / (float)m_Game->var.Height));
	m_Game->var.MTS->D2DDRAW(0, TRUE, NULL, m_BackImage, rc, NULL);
	m_CPNInstance->Paint();
	INT Y_POS = 0;
	//for (int i = 0; i < 9; i++)
	//{
	//	back_rc = { 88,90 + Y_POS,713,126 + Y_POS };
	//	if (BackKey == i)
	//	{
	//		game->var.MTS->D2DDRAW(0, BackStrip[1], back_rc);
	//	}
	//	else
	//	{
	//		game->var.MTS->D2DDRAW(0, BackStrip[0], back_rc);
	//	}
	//
	//	if ((MusicKey + i) < MusicName.size())
	//	{
	//		COLOR co = { 0.94,0.47f,0.47f,0.8f };
	//		game->var.MTS->D2DLOADTXT(back_rc,MusicName[MusicKey + i], wcslen(MusicName[MusicKey + i]), co);
	//	}
	//	Y_POS += 50;
	//}

	//game->var.MTS->EndDraw();

}

void MUSIC::OpenKey()
{
	m_CPNInstance->OpenConponent();
	//CONPONENT *t_Conponent = m_CPNInstance->Find("MusicQuit");
	//t_Conponent->SetState(true);
	//t_Conponent = m_CPNInstance->Find("MusicMinimize");
	//t_Conponent->SetState(true);
	//t_Conponent = m_CPNInstance->Find("MusicStrip1");
	//t_Conponent->SetState(true);
	//t_Conponent = m_CPNInstance->Find("MusicPos");
	//t_Conponent->SetState(true);
	//t_Conponent = m_CPNInstance->Find("MusicPlay");
	//t_Conponent->SetState(true);

}

void  MUSIC::CloceKey()
{
	m_CPNInstance->CloseConponent();
	//CONPONENT *t_Conponent = m_CPNInstance->Find("MusicQuit");
	//t_Conponent->SetState(false);
	//t_Conponent = m_CPNInstance->Find("MusicMinimize");
	//t_Conponent->SetState(false);
	//t_Conponent = m_CPNInstance->Find("MusicStrip1");
	//t_Conponent->SetState(false);
	//t_Conponent = m_CPNInstance->Find("MusicPos");
	//t_Conponent->SetState(false);
	//t_Conponent = m_CPNInstance->Find("MusicPlay");
	//t_Conponent->SetState(false);
}

int MUSIC::GetMusicState()
{
	return m_MusicState;
}

void MUSIC::LoadMusicUI(MusicUI *&UIHead)
{
	char arr[64];
	memset(arr, 0, 64);
	strcat(arr, "UI//Music//");
	strcat(arr, UIHead->filename);
	strcat(arr, ".png");
	m_Game->var.MTS->MyLoadImage(tool->s2ws(arr), UIHead->image);
}

void MUSIC::OpenMusicRoom()
{
	OpenKey();
	m_MusicState = OPENMUSICROOM;
}

void MUSIC::CloceMusicRoom()
{
	CloceKey();
	m_MusicState = CLOCEMUSICROOM;
}

void MUSIC::BACKSSTATEMusicRoom()
{
	CloceKey();
	m_MusicState = BACKSSTATE;
}

void MUSIC::SetPlayModel(int t_model)
{
	m_PlayModel = t_model;
}

BOOL MUSIC::GetMusicRoomState()
{
	return m_MusicState;
}

BOOL MUSIC::CurSorJudge(Point2DXY t_CurPos, WORD t_type)
{
	m_CPNInstance->CurPosJudge(t_CurPos, t_type);
	return TRUE;
}

INT MUSIC::GetConponentCompare()
{
	return m_CPNInstance->GetState();
}

string *MUSIC::GetCurPlay()
{
	return &m_CurPlay.m_Name;
}

void MUSIC::PlayOneMusic(const char *filename)
{
	Fmusic.PlayOnceAudio(filename);
}

void MUSIC::ContinueLoopMusic()
{
	m_PlayState = CURRENTPLAY;
	if (m_CurPlay.m_Name[0] == 0)
	{
		PlayNextMusic();
		return;
	}
	//SetPlayPos(m_CurPlay.m_Loaction);
	Fmusic.ContinueCurrentPlay((unsigned int)m_CurPlay.m_Loaction);
}

void MUSIC::StopLoopMusic()
{
	m_PlayState = STOPPLAY;
	m_CurPlay.m_Loaction = (float)Fmusic.GetCurrentPlayPos();
	Fmusic.StopLoopAudio(m_CurPlay.m_Name.c_str());
}

void MUSIC::SetPlayPos(unsigned int pos)
{
	m_CurPlay.m_Loaction = (float)pos;
	if (!m_PlayState)
		;
	else
		ContinueLoopMusic();
}

float MUSIC::GetPlayPos()
{
	return ((m_CurPlay.m_Loaction = (float)Fmusic.GetCurrentPlayPos()) / 40000.0f);
}

void MUSIC::PlayLoopMusic(const char *filename)
{
	if (!m_CurPlay.m_Name[0])
	{
		Fmusic.PlayLoopAudio(filename);
		m_CurPlay.m_Name.clear();
		m_CurPlay.m_Name = filename;

	}
	else
	{
		//Fmusic.CloceLoopAudio(m_CurPlay.m_Name.c_str());
		Fmusic.PlayLoopAudio(filename);
		m_CurPlay.m_Name.clear();
		m_CurPlay.m_Name = filename;
	}
	//m_CurPlay.m_Lenth = (float)Fmusic.GetMusicLenth(m_CurPlay.m_Name.c_str());
	//CONPONENT *t_Conponent;
	//t_Conponent = m_CPNInstance->Find(MUSIC_POS);
	//t_Conponent->ResetPos();
	m_PlayState = CURRENTPLAY;
	m_CurPlay.m_Loaction = 0;
}

int MUSIC::GetOneVolume()
{
	return Fmusic.GetOnceVolume();
}

int MUSIC::GetLoopVolume()
{
	return Fmusic.GetLoopVolume();
}

void MUSIC::SetOneVolume(int num)
{
	Fmusic.SetOnceVolume(num);
}

void MUSIC::SetLoopVolume(int num)
{
	Fmusic.SetLoopVolume(num);
}

void MUSIC::LoadLoopMusic(char *filename, const char *fileway, bool NOImage)
{
	if (!NOImage)
	{
		MusicUI *ui = new MusicUI;
		ui->filename = filename;
		LoadMusicUI(ui);
		MusicGather.push_back(ui);
	}
	Fmusic.PushLoopAudio(filename, fileway);
}

void MUSIC::LoadOneMusic(const char *filename, const char *fileway)
{
	Fmusic.PushOnceAudio(filename, fileway);
}

void MUSIC::AddMusic(WCHAR *filename)
{
	MusicName.push_back(filename);
}

void MUSIC::DeleteCurPlayMusic()
{
	Fmusic.DeleteMusic(m_CurPlay.m_Name.c_str());
}

void MUSIC::PlayNextMusic()
{
	if (m_PlayListing == ONESONGCURCULATE)
	{
		PlayLoopMusic(m_CurPlay.m_Name.c_str());
	}
	else if (m_PlayListing == LISTINGCURCULATE)
	{
		m_LibraryFind = m_MusicLibrary.find(m_CurPlay.m_Name);
		if (m_LibraryFind != m_MusicLibrary.end())
			m_LibraryFind++;
		if (m_LibraryFind == m_MusicLibrary.end())
		{
			m_LibraryFind = m_MusicLibrary.begin();
		}
		Fmusic.PushLoopAudio(m_LibraryFind->second->m_Name.c_str(), m_LibraryFind->second->m_FileWay);
		PlayLoopMusic(m_LibraryFind->second->m_Name.c_str());
	}
	else if (m_PlayListing == ORDERPLAY)
	{
		m_LibraryFind = m_MusicLibrary.begin();
		int t_Appoint = rand() % m_MusicLibrary.size();
		for (int i = 0; i < t_Appoint; i++)
		{
			m_LibraryFind++;
		}
		if (memcmp(m_LibraryFind->second->m_Name.c_str(), m_CurPlay.m_Name.c_str(), sizeof(m_LibraryFind->second->m_Name)))
		{
			m_LibraryFind++;
		}
		Fmusic.PushLoopAudio(m_LibraryFind->second->m_Name.c_str(), m_LibraryFind->second->m_FileWay);
		PlayLoopMusic(m_LibraryFind->second->m_Name.c_str());
	}

}

void MUSIC::WhetherNext()
{
	m_CurPlay.m_Loaction = (float)Fmusic.GetCurrentPlayPos();
	if ((m_CurPlay.m_Loaction) >= (m_CurPlay.m_Lenth - 1000))
	{
		if (m_PlayState == CURRENTPLAY)
			PlayNextMusic();
	}
}

int MUSIC::GetPlayState()
{
	return m_PlayState;
}
//设置播放状态
void MUSIC::SetPlayState(int t_state)
{
	m_PlayState = t_state;
}

int MUSIC::GetLlenth()
{
	return (int)m_CurPlay.m_Lenth;

}

void MUSIC::LoadMusicFile()
{

	long t_File = 0;
	_finddata_t fileinfo;
	string p;
	vector<char *>t_Filename;
	char *arr3;
	if ((t_File = _findfirst(p.assign("Music//BGM//").append("//*").c_str(), &fileinfo)) != -1)
	{

		do
		{

			if ((fileinfo.attrib & _A_SUBDIR))
				;
			else
			{
				arr3 = (char *)malloc(64);
				memset(arr3, 0, 64);
				strcat(arr3, fileinfo.name);
				t_Filename.push_back(arr3);
				arr3 = 0;
			}
		} while (_findnext(t_File, &fileinfo) == 0);
		_findclose(t_File);
	}
	char arr1[64] = { 0 };
	char arr2[64] = { 0 };
	vector<char *>::iterator t_Find = t_Filename.begin();
	for (int i = 1; t_Find != t_Filename.end(); t_Find++, i++)
	{
		memset(arr1, 0, 64);
		sprintf(arr1, "%d", i);
		WritePrivateProfileStringA((LPCSTR)(arr1), (LPCSTR)"FileName", (LPCSTR)(*t_Find), (LPCSTR)"UI//Music//Information.ini");
	}



	//写出   只要编号不重叠就可以继续添加
	//WritePrivateProfileStringA((LPCSTR)(arr1), (LPCSTR)"X", (LPCSTR)arr2, (LPCSTR)"Map//Map.ini");
	for (int i = 1; i < 10000; i++)
	{
		memset(arr1, 0, 64);
		memset(arr2, 0, 64);
		sprintf(arr1, "%d", i);
		//获取音乐名
		if (!GetPrivateProfileStringA(arr1, (LPCSTR) "FileName", 0, arr2, 64, "UI//Music//Information.ini"))
			break;
		memset(arr1, 0, 64);
		//获取音乐所在路劲
		strcat(arr1, "Music//BGM//");
		strcat(arr1, arr2);

		//删除掉.mp3
		int t_size = strlen(arr2);
		for (int i = t_size - 1; i >= 0; i--)
		{
			if (arr2[i] != 0)
			{
				if (arr2[i] != '.')
				{
					arr2[i] = 0;
				}
				else
				{
					arr2[i] = 0;
					break;
				}
			}
		}
		//arr2[t_size - 1] = 0;
		//arr2[t_size - 2] = 0;
		//arr2[t_size - 3] = 0;
		//arr2[t_size - 4] = 0;
		//加入音乐信息结构
		MUSICINFORMATION *t_MusicInformation = new MUSICINFORMATION;
		int t_Len1 = strlen(arr2) + 1;
		int t_Len2 = strlen(arr1) + 1;
		char *arr4 = (char *)malloc(t_Len1);
		char *arr5 = (char *)malloc(t_Len2);
		memset(arr4, 0, strlen(arr2));
		strcat(arr4, arr2);
		memset(arr5, 0, strlen(arr1));
		strcat(arr5, arr1);
		t_MusicInformation->m_Name = arr4;
		t_MusicInformation->m_FileWay = arr5;
		//加入音乐库
		sprintf(arr2, "%c", i);
		string s = arr4;
		m_MusicLibrary[s] = t_MusicInformation;
	}

}