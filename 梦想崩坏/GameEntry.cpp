#include "GameEntry.h"
#include "SceneHead.h"
#include <objbase.h>
#include "Buttom.h"
#include "Scene.h"
#include "Gif.h"
GAMES *GAMES::poi_Game;

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdline,
	int nCmdShow)
{
	GAMES *game = GAMES::GetInstance();
	game->MyRegisterClass(hInstance);
	if (game->InitInstance(hInstance, nCmdShow))
	{
		if (!game->Run())
			return FALSE;
	}

	return 0;
}


ATOM GAMES::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = (LPCWSTR)("canvas");
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

BOOL GAMES::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	srand(unsigned int(time(NULL)));
	HWND hWnd = CreateWindowW((LPCWSTR)("canvas"), TEXT("次元幻想"), WS_POPUP,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	//var.Width = GetSystemMetrics(SM_CXSCREEN);
	//var.Height = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(hWnd, 0, 0, 1066,600, false);


	var.MTS = new _BMDRAWMTL;
	var.hWnd = hWnd;
	if (!var.MTS->InitToolSet(var.hWnd))
	{
		var.MTS->InitToolSet(var.hWnd);
	}
	MoveWindow(hWnd, 0, 0, 1, 1, false);
	ShowWindow(hWnd, nCmdShow);
	var.Width = 1066;
	var.Height = 600;

	START *t_Start = new START;
	t_Start->SetInitKey();
	Scene["Start"] = t_Start;

	CurScene = Scene.find("Start");
	MoveWindow(hWnd, 0, 0, 1066, 600, false);
	ShowWindow(hWnd, nCmdShow);

	return TRUE;
}

void GAMES::ResourceLoad()
{

	GIFIMAGE image;
	RECT rc = { 200,300,400,400 };
	float pre, cur;
	pre = (float)clock();
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);
	float rHalfX = 0;
	float rHalfY = 0;
	float lHalfX = X / 2.0f;
	float lHalfY = Y / 2.0f;
	float AddX = (float)lHalfX / X;
	float AddY = (float)lHalfY / Y;
	float ss = ((float)Y / (float)X);
	AddX += ss;
	AddY = AddX / 2;
	AddY += AddY / 2 / 2 / 2;
	image.LoadGifImage(TEXT("UI//StartScene//sss"), rc);
	int pre2 = clock();
	while (1)
	{
		cur = (float)clock();

		//ShowWindow(var._hWnd, SW_NORMAL);
		if ((cur - pre2) > 2 && (rHalfX - lHalfX) < WINWIDTH && (rHalfY - lHalfY) < (WINHEIGHT))
		{
			MoveWindow(var.hWnd, lHalfX, lHalfY, rHalfX, rHalfY, true);
			pre2 = clock();
			lHalfX -= (AddX * 20);
			lHalfY -= (AddY * 20);
			rHalfX += (AddX * 2 * 20);
			rHalfY += (AddY * 2 * 20);
		}

		if (cur - pre > 1500)
			break;
		var.MTS->BeginDraw();
		/*image.Paint();*/
		var.MTS->EndDraw();
	}
}

BOOL GAMES::Run()
{
	ResourceLoad();
	//游戏循环
	while (1)
	{
		if (!CurScene->second)
		{
			return FALSE;
		}
		CurScene->second->InitScene();
		if (!CurScene->second->Run())
		{
			if (CurScene->first == "Start")
				break;
			CurScene = Scene.find("Start");
		}
	}
	return FALSE;
}

void GAMES::AddScene(char *t_name, GAMESCENE *t_c)
{
	if(Scene.find(t_name) == Scene.end())
		Scene[t_name] = t_c;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GAMES *game = GAMES::GetInstance();
	switch (message)
	{
	case WM_PAINT:
	{
		game->var.MTS->BeginDraw();
		game->CurScene->second->MyPaint();
		game->var.MTS->EndDraw();
	}break;
	case WM_LBUTTONDOWN:
	{
		float x = LOWORD(lParam);
		float y = HIWORD(lParam);
		RECT rc;
		GetWindowRect(game->var.hWnd, &rc);
		float X = (((float)rc.right - (float)rc.left) / (float)game->var.Width);
		float Y = (((float)rc.bottom - (float)rc.top) / (float)game->var.Height);
		x /= X;
		y /= Y;
		PointXY CurPos = { x,y };
		game->CurScene->second->PressDown(CurPos);
	}break;
	case WM_LBUTTONUP:
	{
		float x = LOWORD(lParam);
		float y = HIWORD(lParam);
		RECT rc;
		GetWindowRect(game->var.hWnd, &rc);
		float X = (((float)rc.right - (float)rc.left) / (float)game->var.Width);
		float Y = (((float)rc.bottom - (float)rc.top) / (float)game->var.Height);
		x /= X;
		y /= Y;
		PointXY CurPos = { x,y };
		game->CurScene->second->UpCursor();
		game->CurScene->second->ButtomJudge(&CurPos, LCURSORSINGLECLICK);
	}break;
	case WM_DESTROY:
		DeleteObject(game->var.hWnd);
		game->var.MTS->Destroy();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
