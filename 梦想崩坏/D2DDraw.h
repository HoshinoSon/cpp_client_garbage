#pragma once
#pragma once
#ifndef MY_D2DDRAW
#define MY_D2DDRAW
#pragma warning(disable:4005)
#pragma warning(disable:4091)
#pragma warning(disable:4616)
#pragma warning(disable:4083)
#pragma warning(disable:4996)
#pragma warning(disable:4800)
#pragma warning(disable:4806)
#include <D2D1.h>
#include <wincodec.h>  
#include <dwrite.h>
#include <winbase.h>
#include <iostream>
#include <windows.h>
//#pragma comment(lib,"kerne132.lib")
#pragma comment(lib, "d2d1.lib")  
#pragma comment(lib, "Dwrite.lib")

typedef ID2D1Bitmap Bitmap;

typedef struct PointCoorDinate
{
	float x, y;
}*Point2DXY, PointXY;

struct COLOR
{
	FLOAT R;
	FLOAT G;
	FLOAT B;
	FLOAT A;
};

struct PNGINFOHEADER
{
	//像素宽
	unsigned short m_Width;
	//像素高
	unsigned short m_Height;
	//图像深度
	char depth;
	//颜色类型
	//0 灰度
	char ColorType;
	//压缩方法
	BYTE CompressionMethod;
	//滤波器方法
	BYTE FuterMethod;
	//是否隔行扫描
	BYTE InterlaceMethod;
};

//图片结构
struct Point2D
{
	RECT rc;
	Bitmap *Bitmap;
};

typedef struct MyToolSet
{

	ID2D1HwndRenderTarget	 *HRDT = NULL;			//主要设备 HWND，所有操作都由这个进行
	IWICImagingFactory		 *IWIIF = NULL;			//主要设备 IMAGE 主要用于读取文件和转换
	ID2D1Factory			 *id2dFactory = NULL;	//主要设备 Factory 主要用于初始化

													//次要设备，主要是画刷等
	ID2D1SolidColorBrush	 *pBlackBrush = NULL;	//黑色画刷
	ID2D1SolidColorBrush     *pWhiteBrush = NULL;   //白色画刷
	IDWriteFactory			 *WF = NULL;			//文字设备
	IDWriteTextFormat		 *WTF = NULL;			//用于设置文本格式的设备
	IDWriteTextLayout		 *WTL = NULL;			//用于设置文本布局的设备


	int InitToolSet(HWND hwnd);	//初始化所有设备
	void BeginDraw();			//开始
								//绘制图形 参数依次是:角度，透明度,中心点,Point图形结构，绘制在什么地方的矩形
	void D2DDRAW(float angle, float opacity, RECT *t_Center, CONST Point2D *image, RECT draw_rc,RECT *tailor_rc);
	//绘制TXT  参数是:  1.绘制TXT的矩形，如果一排写不下并且高度是第一排的二倍那么将在第二排绘制；
	//					2.为要绘制的文字
	//                  3.绘制多少个像素宽
	void D2DLOADTXT(CONST RECT poi, WCHAR *string, DWORD size_t, COLOR color);
	void EndDraw();				//结束
	void Destroy();				//程序结束
	BOOL MyLoadImage(CONST WCHAR *filename, Point2D *&pWH);	//读取图片
	BOOL MyLoadImageFromResource(CONST INT &filename, CONST WCHAR *lpType, Point2D *&pWH);
	BOOL MyLoadImageFromStream(CONST WCHAR *filename, Point2D *&pWH);
}_BMDRAWMTL, *BMDRAWMTL;
#endif