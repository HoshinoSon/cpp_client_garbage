
#include "GameEntry.h"
//#include "Figure.h"
using namespace std;


Input *Input::m_Input;
TOOLSET *TOOLSET::tool;
DMK *DMK::dmk;
bool TOOLSET::Times(MyTimer &times)
{
	//计算时间差
	times.Cur = (float)clock();
	return (times.Cur - times.Pre) > times.Interval ? (times.Pre = (float)clock()) && true : false;
}

void TOOLSET::Centre(PointXY &Pos, PointXY WH)
{
	Pos.x = Pos.x - ((int)WH.x >> 1);
	Pos.y = Pos.y - ((int)WH.y >> 1);
}

char* TOOLSET::ws2s(const wstring & ws)
{
	size_t convertedChars = 0;
	string curLocale = setlocale(LC_ALL, NULL); //curLocale="C"
	setlocale(LC_ALL, "chs");
	const wchar_t* wcs = ws.c_str();
	size_t dByteNum = sizeof(WCHAR)*ws.size() + 1;

	char* dest = new char[dByteNum];
	wcstombs_s(&convertedChars, dest, dByteNum, wcs, _TRUNCATE);
	char* result = dest;
	return result;
}

WCHAR * TOOLSET::s2ws(const string & s)
{
	size_t convertedChars = 0;
	string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const char* source = s.c_str();
	size_t charNum = sizeof(char)*s.size() + 1;

	WCHAR* dest = new WCHAR[charNum];
	mbstowcs_s(&convertedChars, dest, charNum, source, _TRUNCATE);
	WCHAR *result = dest;
	return result;
}
float TOOLSET::My_Sqrt(float x)
{
	float f1 = 0.5f;
	float f2 = 1.5f;
	float half = f1 * x;
	int i = *(int *)&x;
	i = 0x5f3759df - (i >> 1); // 计算第一个近似根
	x = *(float*)&i;
	x = x*(f2 - half * x * x); // 牛顿迭代法
	return 1 / x;
}

void TOOLSET::SreenCoordinate(PointXY &Pos)
{
	RECT rc;
	GAMES *t_Game = GAMES::GetInstance();
	GetWindowRect(t_Game->var.hWnd, &rc);
	float X = (((float)rc.right - (float)rc.left * 2) / (float)t_Game->var.Width);
	float Y = (((float)rc.bottom - (float)rc.top * 2) / (float)t_Game->var.Height);
	if ((X - (int)X) < 0.001)
		X -= X - (int)X;
	Pos.x /= X;
	Pos.y /= Y;
}

//判断距离
INT TOOLSET::My_Distance(Point2DXY Object1, Point2DXY Object2)
{
	float slope = (Object2->x - Object1->x) * (Object2->x - Object1->x) +
		(Object2->y - Object1->y) * (Object2->y - Object1->y);
	return (INT)(1 / My_Sqrt(slope));
}

double TOOLSET::StoA(float x1, float y1, float x2, float y2)
{
	//计算两点连线的角度
	return atan2(y2 - y1, x2 - x1) * 180 / pi;
}

Clock::Clock()
{
	this->startTime = time(NULL);
	this->CurTime = this->startTime;
}

Time_Value Clock::UpTime()
{
	return this->CurTime = time(NULL);
}

Time_Value Clock::GetSustainTime()
{
	return (float)time(NULL) - (float)startTime;
}



void DMK::InitMmr()
{
	RunTime.Pre = (float)clock();
	RunTime.Interval = 2;
	InitMemoriSA(DCMFHead);
	GAMES *game = GAMES::GetInstance();
	game->var.MTS->MyLoadImage(TEXT("UI//Figure//Bullet//bullet1.png"), FSkillChartLet[0]);
};

void DMK::SetSTC(STC &skill_type, SKILLTYPE type1, SKILLTYPE type2, SKILLTYPE type3, SKILLTYPE type4)
{
	skill_type.Type1 = type1;
	skill_type.Type2 = type2;
	skill_type.Type3 = type3;
	skill_type.Type4 = type4;
}

//DMKCVMMR &DMK::GetDMKCVHead(INT slope)
//{
//	if (slope == SLOPE_ONE) return DCMOHead;
//	if (slope == SLOPE_TWO) return DCMTHead;
//	if (slope == SLOPE_THREE) return DCMSHead;
//}
//DMKSAMMR &DMK::GetDMKSAHead(INT slope)
//{
//	if (slope == SLOPE_ONE) return DSMOHead;
//	if (slope == SLOPE_TWO) return DSMTHead;
//	if (slope == SLOPE_THREE) return DSMSHead;
//}

void *DMK::NewStraight()
{
	return 0;
}

void *DMK::NewCurva()
{
	return 0;
}

void DMK::InitMemoriSA(DMKSAMMR &mmr)
{
	DSMMHead = new newDMKSAMMR;
	DSMMHead->next = 0;
	DSMMHead->prev = 0;
	mmr = new newDMKSAMMR;
	mmr->next = 0;
	mmr->prev = 0;
	dmksammr = new newDMKSAMMR;
	DMKSAMMR P = dmksammr;
	P->next = 0;
	for (int i = 0; i < 10000; i++)
	{
		if (!P->next)
		{
			DMKSAMMR P1;
			P1 = new newDMKSAMMR;
			P->next = P1;
			P1->next = 0;
			P1->prev = P;
			continue;
		}
		DMKSAMMR P1;
		P1 = new newDMKSAMMR;
		P1->next = P->next;
		P1->prev = P->next->prev;
		P->next->prev = P1;
		P->next = P1;
	}
}


void DMK::InitMemoriCV(DMKCVMMR &mmr)
{
	mmr = new newDMKCVMMR;
	DMKCVMMR P = dmkcvmmr;
	for (int i = 0; i < 10000; i++)
	{
		DMKCVMMR P1;
		P1 = new newDMKCVMMR;
		P1->next = P->next;
		P1->prev = P->next->prev;
		P->next->prev = P1;
		P->next = P1;
	}
}


void *DMK::NewSA(DMKSAMMR &Head)
{
	for (DMKSAMMR P = dmksammr->next;; P = P->next)
	{
		if (!P)
		{
			break;
		}
		P->next->prev = P->prev;
		P->prev->next = P->next;
		if (!Head->next)
		{
			Head->next = P;
			P->prev = Head;
			P->next = 0;
			return P;
		}
		P->next = Head->next;
		Head->next->prev = P;
		P->prev = Head;
		Head->next = P;
		return P;
	}
	return 0;
}

void *DMK::NewCV(DMKCVMMR &Head)
{
	for (DMKCVMMR P = dmkcvmmr->next;; P = P->next)
	{
		if (!P)
		{
			break;
		}
		P->next->prev = P->prev;
		P->prev->next = P->next;

		P->next = Head->next;
		Head->next->prev = P;
		P->prev = Head;
		Head->next = P;
		return P;
	}
	return 0;
}

void DMK::DelSA(DMKSAMMR Node)
{
	if (!Node->next)
	{
		dmksammr->next->prev = Node;
		Node->prev->next = 0;
		Node->next = dmksammr->next;
		Node->prev = dmksammr;
		dmksammr->next = Node;
		return;
	}
	Node->next->prev = Node->prev;
	Node->prev->next = Node->next;
	Node->next = 0;
	for (DMKSAMMR P1 = dmksammr;; P1 = P1->next)
	{
		if (!P1->next)
		{
			P1->next = Node;
			break;
		}
		else
		{
			Node->next = P1->next;
			P1->next->prev = Node;
			Node->prev = P1;
			P1->next = Node;
			break;
		}
	}
}

void DMK::DelCV(DMKCVMMR Node)
{
	if (!Node->next)
		return;
	Node->next->prev = Node->prev;
	Node->prev->next = Node->next;
	for (DMKCVMMR P1 = dmkcvmmr;; P1 = P1->next)
	{
		if (!P1->next)
		{
			P1->next = Node;
			break;
		}
		else
		{
			Node->next = P1->next;
			P1->next->prev = Node;
			Node->prev = P1;
			P1->next = Node;
			break;
		}
	}
}



Angle DMK::Means_two_s(Angle slope, int &cur, int &max, INT what_is_bullet, PointXY Pos, STC stc, INT image)
{
	DMKSAMMR f_s_P = 0;
	DMKSAMMR P;
	static ROLE *figure;
	if (cur < max)
	{
		P = (DMKSAMMR)NewSA(f_s_P);
		int temp_angle;

		P->data.LocaTion.x = Pos.x;
		P->data.LocaTion.y = Pos.y;
		P->data.Harm = 10;
		P->data.Type = stc;
		slope.vk_x = P->data.VK.x = (float)(slope.vk_x * cos(slope.slope) - slope.vk_y * sin(slope.slope));
		slope.vk_y = P->data.VK.y = (float)(slope.vk_x * sin(slope.slope) + slope.vk_y * cos(slope.slope));
		slope.angle = P->data.Angle = (slope.slope > 0 ? slope.angle + 10 : slope.angle - 10 < 0 ? 360 - (slope.angle - 10 * -1) : slope.angle - 10) >= 360 ?
			(slope.slope > 0 ? slope.angle + 10 : slope.angle - 10 < 0 ? 360 - (slope.angle - 10 * -1) : slope.angle - 10) - 360 :
			(slope.slope > 0 ? slope.angle + 10 : slope.angle - 10 < 0 ? 360 - (slope.angle - 10 * -1) : slope.angle - 10);
		temp_angle = (INT)(P->data.Angle / 5);
		P->data.Image = image;

		cur++;
	}
	return slope;
}

bool DMK::Means_two_m(Angle slope, int &cur, int &max, INT what_is_bullet, PointXY Pos, STC stc, INT image)
{
	static Angle cur_slope;
	if (cur == 0)
		cur_slope = slope;
	Angle temp_angle = Means_two_s(slope, cur, max, what_is_bullet, Pos, stc, image);

	if (cur < max && !temp_angle.key)
	{
		temp_angle.key = Means_two_m(temp_angle, cur, max, what_is_bullet, Pos, stc, image);
	}
	if ((cur == max) && !temp_angle.key)
	{
		cur = 0;
		temp_angle = cur_slope;
		temp_angle.slope *= -1;
		temp_angle.key = true;
	}
	if (cur < max && temp_angle.key)
	{
		temp_angle.key = Means_two_m(temp_angle, cur, max, what_is_bullet, Pos, stc, image);
	}
	return cur == max ? true : false;
}

//圆形
void DMK::BulletRoundNess(DMKSAMMR &head, CONST Point2D _image, CONST SKILLTYPE _st,
	CONST INT _angle, INT Slope, INT what_is_bullet, PointXY Pos, STC stc, INT image)
{
	//int temp_angle;
	//DMKSAMMR P1;
	//static SKILLTYPE g_St;
	//for (int i = 1; i <= ((360 >> (_angle >> 1)) >> 1) + 1; i++)
	//{
	//	P1 = (DMKSAMMR)New(GetDMKSAHead(Slope));
	//	P1->data.LocaTion = head->data.LocaTion;
	//	slope = (double)((i << (_angle >> 1) >> 1) + 1) / 180 * pi;
	//	P1->data.VK.x = head->data.VK.x * cos(slope) - head->data.VK.y * sin(slope);
	//	P1->data.VK.y = head->data.VK.x * sin(slope) + head->data.VK.y * cos(slope);
	//	P1->data.Angle = (head->data.Angle + i * _angle) >= 360 ? (head->data.Angle + i * _angle) - 360 : (head->data.Angle + i * _angle);
	//	P1->data.Image = _image;

	//	SetTimer(P1->data.ExecuteType, 0, 0, 0);

	//	SetSKILLTYPE(g_St, _st.Times, _st.Type);
	//	SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);
	//	// 
	//	P1 = (DMKSAMMR)New(GetDMKSAHead(Slope));
	//	P1->data.LocaTion = head->data.LocaTion;
	//	P1->data.VK->x = head->data.VK->x * cos(-slope) - head->data.VK->y * sin(-slope);
	//	P1->data.VK->y = head->data.VK->x * sin(-slope) + head->data.VK->y * cos(-slope);
	//	P1->data.Angle = (head->data.Angle - i * _angle) >= 0 ? (head->data.Angle - i * _angle) :
	//		360 - (head->data.Angle - i * _angle) * -1;
	//	P1->data.Image = _image;

	//	SetTimer(P1->data.ExecuteType, 0, 0, 0);

	//	SetSKILLTYPE(g_St, _st.Times, _st.Type);
	//	SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);
	//}
	//head->data.LocaTion;
	//slope = (double)((0 << (0 >> 1) >> 1) + 1) / 180 * pi;
	//head->data.VK->x = head->data.VK->x * cos(slope) - head->data.VK->y * sin(slope);
	//head->data.VK->y = head->data.VK->x * sin(slope) + head->data.VK->y * cos(slope);
	//head->data.Angle = 0;
	//head->data.Image = _image;

	//SetTimer(P1->data.ExecuteType, 0, 0, 0);

	//SetSKILLTYPE(g_St, _st.Times, _st.Type);
	//SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);

	//---------------------------------------------------------------------
	int temp_x, temp_y;
	//获得向量
	temp_x = (int)(Pos.x + 100);
	temp_y = (int)(Pos.y + 100);
	//获取当前节点与目标点的角度
	int angle = (int)(atan2(temp_y, temp_x) * 180 / pi);
	int cur = 0;
	//如果填 3   左方向和右方向各1节点 / 初始节点也占用1
	int max = 1;//Quantity;
				//设置第一个目标点属性
	Angle _one;
	_one.angle = (float)angle;
	_one.key = true;
	_one.slope = 0;
	_one.vk_x = 0.500000f;
	_one.vk_y = 0.500000f;
	//生成第一个对象
	Means_two_m(_one, cur, max, what_is_bullet, Pos, stc, image);

	cur = 0;
	max = 18;
	//统一10.0角度的偏移量
	double slope = (double)(10.0 / 180 * pi);
	Angle a_s;
	//初始化节点属性
	a_s.angle = (float)angle;
	a_s.slope = slope;
	a_s.vk_x = 0.500000f;
	a_s.vk_y = 0.500000f;
	a_s.key = false;
	//开始构造
	Means_two_m(a_s, cur, max, what_is_bullet, Pos, stc, image);
}
//
//void DMK::BulletSector(DMKSAMMR &head, INT _angle, INT radius, Point2D _image, CONST SKILLTYPE _st, CONST MyTimer _times, INT Slope)
//{
//	DMKSAMMR P1;
//	double slope;
//	static MyTimer g_Times;
//	static SKILLTYPE g_St;
//	for (int i = 1; i <= radius; i++)
//	{
//		P1 = (DMKSAMMR)New(GetDMKSAHead(Slope));
//		P1->data.LocaTion = head->data.LocaTion;
//		slope = (double)(P1->data.Angle = ((((i << (_angle >> 1)) + 1) + head->data.Angle) + 1) > 360 ?
//			P1->data.Angle = 360 - P1->data.Angle : P1->data.Angle) / 180 * pi;
//		P1->data.VK->x = head->data.VK->x * cos(slope) - head->data.VK->y * sin(slope);
//		P1->data.VK->y = head->data.VK->x * sin(slope) + head->data.VK->y * cos(slope);
//		P1->data.Image = _image;
//
//		SetTimer(P1->data.ExecuteType, 0, 0, 0);
//
//		SetSKILLTYPE(g_St, _st.Times, _st.Type);
//		SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);
//
//		// 
//		P1 = (DMKSAMMR)New(GetDMKSAHead(Slope));
//		P1->data.LocaTion = head->data.LocaTion;
//		slope = (double)(P1->data.Angle = (head->data.Angle - ((i << (_angle >> 1)) + 1) + 1) < 0 ?
//			360 - (P1->data.Angle * -1) : P1->data.Angle) / 180 * pi;
//		P1->data.VK->x = head->data.VK->x * cos(-slope) - head->data.VK->y * sin(-slope);
//		P1->data.VK->y = head->data.VK->x * sin(-slope) + head->data.VK->y * cos(-slope);
//		P1->data.Image = _image;
//
//		SetTimer(P1->data.ExecuteType, 0, 0, 0);
//
//		SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);
//	}
//}
//
//void  DMK::FissionMirroring(DMKSAMMR &head, DMKSAMMR &node, INT _angle, Point2D _image, CONST SKILLTYPE _st, INT Slope)
//{
//	DMKSAMMR P1;
//	double slope;
//	static SKILLTYPE g_St;
//
//	P1 = (DMKSAMMR)New(GetDMKSAHead(Slope));
//	P1->data.LocaTion = head->data.LocaTion;
//	slope = (double)((P1->data.Angle = (_angle + head->data.Angle)) > 360 ?
//		P1->data.Angle = 360 - P1->data.Angle : P1->data.Angle) / 180 * pi;
//	P1->data.VK->x = head->data.VK->x * cos(slope) - head->data.VK->y * sin(slope);
//	P1->data.VK->y = head->data.VK->x * sin(slope) + head->data.VK->y * cos(slope);
//	P1->data.Image = &_image;
//	SetTimer(P1->data.ExecuteType, 0, 0, 0);
//	g_St = _st;
//	SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);
//
//
//	P1 = (DMKSAMMR)New(GetDMKSAHead(Slope));
//	P1->data.LocaTion = head->data.LocaTion;
//	slope = (double)((P1->data.Angle = head->data.Angle - _angle)  < 0 ?
//		360 - (P1->data.Angle * -1) : P1->data.Angle) / 180 * pi;
//	P1->data.VK->x = head->data.VK->x * cos(-slope) - head->data.VK->y * sin(-slope);
//	P1->data.VK->y = head->data.VK->x * sin(-slope) + head->data.VK->y * cos(-slope);
//	P1->data.Image = &_image;
//	SetTimer(P1->data.ExecuteType, 0, 0, 0);
//	SetSTC(P1->data.Type, g_St, g_St, g_St, g_St);
//}

void DMK::FissionDisperse(DMKCVMMR &head, size_t size, INT angle, INT Slope)
{

}

void DMK::BezierCurva(Point2DXY &object_pos, CONST Point2DXY location_state, CONST Point2DXY location1,
	CONST Point2DXY location2, CONST Point2DXY location_goal, INT Slope)
{

}

void DMK::BulletRoundNess(CURVA type, INT Slope)
{

}

void DMK::BulletSector(INT angle, INT Slope)
{

}

void DMK::FissionMirroring(DMKCVMMR &head, INT angle, INT Slope)
{

}

void DMK::FissionDisperse(size_t size, INT angle, INT Slope)
{

}

void  DMK::SetTimer(MyTimer &times, INT cur, INT pre, INT interval)
{
	times.Cur = (float)cur;
	times.Pre = (float)pre;
	times.Interval = (float)interval;
}

void  DMK::SetSKILLTYPE(SKILLTYPE &st, MyTimer times, INT type)
{
	st.Times = times;
	st.Type = type;
}

void DMK::Run()
{
	GAMES *game = GAMES::GetInstance();
	tool = TOOLSET::GetTool();
	if (tool->Times(RunTime))
	{
		for (DMKSAMMR P = DCMFHead->next; P; )
		{
			P->data.LocaTion.x += P->data.VK.x;
			P->data.LocaTion.y += P->data.VK.y;
			if (P->data.LocaTion.x > 900 || P->data.LocaTion.x < (0 - 150) || P->data.LocaTion.y > 600 || P->data.LocaTion.y < (0 - 150))
			{
				DMKSAMMR P2 = P->next;
				dmk->DelSA(P);
				P = P2;
			}
			else
			{
				P = P->next;
			}
		}
	}
}

void DMK::Draw()
{
	GAMES *game = GAMES::GetInstance();
	RECT drc;
	RECT t_WinRc;
	GetWindowRect(game->var.hWnd, &t_WinRc);
	for (DMKSAMMR P = DCMFHead->next; P; P = P->next)
	{
		drc.left = (LONG)(P->data.LocaTion.x - (FSkillChartLet[P->data.Image - 1]->rc.right >> 1));
		drc.top = (LONG)(P->data.LocaTion.y - (FSkillChartLet[P->data.Image - 1]->rc.bottom >> 1));
		drc.right = (LONG)(drc.left + FSkillChartLet[P->data.Image - 1]->rc.right);
		drc.bottom = (LONG)(drc.top + FSkillChartLet[P->data.Image - 1]->rc.bottom);
		game->var.MTS->D2DDRAW(P->data.Angle, TRUE, &t_WinRc, FSkillChartLet[P->data.Image - 1], drc,NULL);
	}
	for (DMKSAMMR P = DSMMHead->next; P; P = P->next)
	{
		drc.left = (LONG)(P->data.LocaTion.x - (MSkillChartLet[P->data.Image - 1]->rc.right >> 1));
		drc.top = (LONG)(P->data.LocaTion.y - (MSkillChartLet[P->data.Image - 1]->rc.bottom >> 1));
		drc.right = (LONG)(drc.left + MSkillChartLet[P->data.Image - 1]->rc.right);
		drc.bottom = (LONG)(drc.top + MSkillChartLet[P->data.Image - 1]->rc.bottom);
		game->var.MTS->D2DDRAW(0, TRUE, &t_WinRc, MSkillChartLet[P->data.Image - 1], drc, NULL);
	}

}

void Input::IniInputMgr(int num, int *pKey)
{
	//初始化按键信息
	KeyNum = num;
	Key = (int*)malloc(((sizeof(int)* KeyNum)));
	KeyState = (int*)malloc(((sizeof(int)* KeyNum)));
	for (int i = 0; i < KeyNum; i++)
	{
		Key[i] = pKey[i];
		//默认为持续放开
		KeyState[i] = KEY_KEEP_UP;
	}
}

void Input::CheckKeyState()
{
	//设置按键状态
	for (int i = 0; i < (KeyNum >> 2); i++)
	{
		if (GetAsyncKeyState(Key[i]) & 0x8000)
		{
			if (KeyState[i] == KEY_KEEP_DOWN || KeyState[i] == KEY_CURRENT_DOWN)
				KeyState[i] = KEY_KEEP_DOWN;
			else if (KeyState[i] == KEY_KEEP_UP || KeyState[i] == KEY_CURRENT_UP)
				KeyState[i] = KEY_CURRENT_DOWN;

		}
		else
		{
			if (KeyState[i] == KEY_KEEP_DOWN || KeyState[i] == KEY_CURRENT_DOWN)
				KeyState[i] = KEY_CURRENT_UP;
			else if (KeyState[i] == KEY_KEEP_UP || KeyState[i] == KEY_CURRENT_UP)
				KeyState[i] = KEY_KEEP_UP;
		}
	}
}

int Input::MyGetKeyState(int pos)
{
	return KeyState[pos];
}
