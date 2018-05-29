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
	//���ؿ�
	unsigned short m_Width;
	//���ظ�
	unsigned short m_Height;
	//ͼ�����
	char depth;
	//��ɫ����
	//0 �Ҷ�
	char ColorType;
	//ѹ������
	BYTE CompressionMethod;
	//�˲�������
	BYTE FuterMethod;
	//�Ƿ����ɨ��
	BYTE InterlaceMethod;
};

//ͼƬ�ṹ
struct Point2D
{
	RECT rc;
	Bitmap *Bitmap;
};

typedef struct MyToolSet
{

	ID2D1HwndRenderTarget	 *HRDT = NULL;			//��Ҫ�豸 HWND�����в��������������
	IWICImagingFactory		 *IWIIF = NULL;			//��Ҫ�豸 IMAGE ��Ҫ���ڶ�ȡ�ļ���ת��
	ID2D1Factory			 *id2dFactory = NULL;	//��Ҫ�豸 Factory ��Ҫ���ڳ�ʼ��

													//��Ҫ�豸����Ҫ�ǻ�ˢ��
	ID2D1SolidColorBrush	 *pBlackBrush = NULL;	//��ɫ��ˢ
	ID2D1SolidColorBrush     *pWhiteBrush = NULL;   //��ɫ��ˢ
	IDWriteFactory			 *WF = NULL;			//�����豸
	IDWriteTextFormat		 *WTF = NULL;			//���������ı���ʽ���豸
	IDWriteTextLayout		 *WTL = NULL;			//���������ı����ֵ��豸


	int InitToolSet(HWND hwnd);	//��ʼ�������豸
	void BeginDraw();			//��ʼ
								//����ͼ�� ����������:�Ƕȣ�͸����,���ĵ�,Pointͼ�νṹ��������ʲô�ط��ľ���
	void D2DDRAW(float angle, float opacity, RECT *t_Center, CONST Point2D *image, RECT draw_rc,RECT *tailor_rc);
	//����TXT  ������:  1.����TXT�ľ��Σ����һ��д���²��Ҹ߶��ǵ�һ�ŵĶ�����ô���ڵڶ��Ż��ƣ�
	//					2.ΪҪ���Ƶ�����
	//                  3.���ƶ��ٸ����ؿ�
	void D2DLOADTXT(CONST RECT poi, WCHAR *string, DWORD size_t, COLOR color);
	void EndDraw();				//����
	void Destroy();				//�������
	BOOL MyLoadImage(CONST WCHAR *filename, Point2D *&pWH);	//��ȡͼƬ
	BOOL MyLoadImageFromResource(CONST INT &filename, CONST WCHAR *lpType, Point2D *&pWH);
	BOOL MyLoadImageFromStream(CONST WCHAR *filename, Point2D *&pWH);
}_BMDRAWMTL, *BMDRAWMTL;
#endif