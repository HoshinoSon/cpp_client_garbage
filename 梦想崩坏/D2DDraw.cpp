#ifndef MYD2D_LIB
#define MYD2D_LIB
//#include "Game.h"
#include "D2DDraw.h"
#include <wincodec.h>
#define RELEASE_OBJ(p) if(p)p->Release()
//#pragma comment(lib,"Wincodec")

int MyToolSet::InitToolSet(HWND hwnd)
{
	//初始化D2D窗口对象
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &id2dFactory);

	RECT rc;
	//获取客户区宽高
	GetClientRect(hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	D2D1_HWND_RENDER_TARGET_PROPERTIES hrtprops;
	hrtprops.hwnd = hwnd;
	hrtprops.presentOptions = D2D1_PRESENT_OPTIONS_IMMEDIATELY;//好多人说这个是不等垂直同步的参数
	hrtprops.pixelSize = size;

	//初始化Hwnd
	id2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		hrtprops/*D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top))*/,
		&HRDT);
	HRDT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	//初始化接口
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(IWIIF), (LPVOID*)&IWIIF);
	//初始化文字结构
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		_uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown **>(&WF)
	);

	//初始化文字类型
	WF->CreateTextFormat(
		L"Arial",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f * 96.0f / 72.0f,
		L"en-US",
		&WTF
	);
	//新建画刷
	//HRDT->CreateSolidColorBrush(D2D1::ColorF(0),
	//	&pBlackBrush);
	//HRDT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.7f))),
	//	&pBlackBrush);
	return TRUE;
}

void MyToolSet::D2DLOADTXT(CONST RECT poi, WCHAR *string, DWORD size_t, COLOR color)
{
	//绘制的位置
	D2D1_POINT_2F d2d_2f;
	d2d_2f.x = (float)poi.left;
	d2d_2f.y = (float)poi.top;
	HRDT->SetTransform(D2D1::Matrix3x2F::Identity());
	//创建文字结构
	WF->CreateTextLayout((WCHAR *)string, size_t, WTF, (float)poi.right, (float)poi.bottom, &WTL);
	//新建画刷
	HRDT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(D2D1::ColorF(color.R, color.G, color.B, color.A))),
		&pBlackBrush);
	//绘制文字
	HRDT->DrawTextLayout(d2d_2f, WTL, pBlackBrush);
}

void MyToolSet::BeginDraw()
{
	//开始绘制
	HRDT->BeginDraw();
}

void MyToolSet::EndDraw()
{
	//结束绘制
	HRDT->EndDraw();
}

void MyToolSet::Destroy()
{
	//程序结束
	RELEASE_OBJ(HRDT);
	RELEASE_OBJ(IWIIF);
	RELEASE_OBJ(id2dFactory);
	RELEASE_OBJ(pBlackBrush);
	RELEASE_OBJ(WF);
	RELEASE_OBJ(WTF);
	RELEASE_OBJ(WTL);
}

void MyToolSet::D2DDRAW(float angle, float opacity, RECT *t_Center, CONST Point2D *image, RECT draw_rc, RECT *tailor_rc)
{
	//Matrix3x2F说明
	//Invert    反转
	//
	D2D1::Matrix3x2F s;
	s.Invert();

	//HRDT->FillRectangle(
	//	&rcTransformedBrushRect,
	//	m_pBitmapBrush
	//);
	if (!angle)
		//如果0角度，还原旋转方向为0
		HRDT->SetTransform(D2D1::Matrix3x2F::Identity());
	else
		//如果有角度，将下一次绘制的矩形旋转N角度，旋转中心点为图片中心点
		HRDT->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F((float)((int)draw_rc.left +
		((draw_rc.right - draw_rc.left) >> 1)),
			(int)draw_rc.top + ((draw_rc.bottom - draw_rc.top) >> 1))));
	//在DC绘制区域上需要绘制图片上的矩形区域
	//D2D1(&D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F((int)draw_rc.left + (image->rc.right >> 1),
	//	(int)draw_rc.top + (image->rc.bottom >> 1))));
	//HRDT->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF(500, 500)));
	D2D1_RECT_F imgr0;
	if (!tailor_rc)
		imgr0 = { (float)image->rc.left,(float)image->rc.top,(float)image->rc.right,(float)image->rc.bottom };
	else
		imgr0 = *(D2D1_RECT_F*)tailor_rc;
	//绘制的位置
	D2D1_RECT_F imgr1 = { (float)image->rc.left + (float)draw_rc.left,(float)image->rc.top + (float)draw_rc.top,
		(float)image->rc.left + (float)draw_rc.right ,
		(float)image->rc.top + (float)draw_rc.bottom };
	//绘制
	HRDT->DrawBitmap(image->Bitmap, imgr1, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, imgr0);
}

BOOL MyToolSet::MyLoadImage(CONST WCHAR *filename, Point2D *&pWH)
{
	//初始化临时结构变量
	IWICFormatConverter * fmtcovter = NULL;
	IWICBitmapDecoder *bitmapdecoder = NULL;
	IWICBitmapFrameDecode  *pframe = NULL;

	pWH = new Point2D;

	IWIIF->CreateDecoderFromFilename((LPCWSTR)(filename), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapdecoder);
	if (!bitmapdecoder)
		return FALSE;

	//获取图片转换对象
	pframe = NULL;
	bitmapdecoder->GetFrame(0, &pframe);

	//初始化图像转换结构
	IWIIF->CreateFormatConverter(&fmtcovter);
	//将图片转换成D2D支持的图形模式，保存在获取到的对象中
	fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	IWICBitmapSource *IWICBS;
	IWICBS = (IWICBitmapSource*)fmtcovter;
	IWICBitmap *t_Bitmap = NULL;
	IWIIF->CreateBitmapFromSource(IWICBS, WICBitmapNoCache, &t_Bitmap);

	//获取图片宽高
	UINT t_ImageHeight;
	UINT t_ImageWidth;
	t_Bitmap->GetSize(&t_ImageWidth, &t_ImageHeight);
	pWH->rc.left = 0;
	pWH->rc.top = 0;
	pWH->rc.right = t_ImageWidth;
	pWH->rc.bottom = t_ImageHeight;
	//将转换后的图片附加到D2D的HWND中，必须为绘制用的HWND
	HRDT->CreateBitmapFromWicBitmap(fmtcovter, NULL, &pWH->Bitmap);

	//转换失败
	if (!pWH->Bitmap)
	{
		return FALSE;
	}
	//释放临时结构对象
	fmtcovter->Release();
	pframe->Release();
	bitmapdecoder->Release();
	t_Bitmap->Release();
	return TRUE;
}

BOOL MyToolSet::MyLoadImageFromResource(CONST INT &filename, CONST WCHAR *lpType, Point2D *&pWH)
{
	//初始化临时结构变量
	IWICFormatConverter * fmtcovter = NULL;
	IWICBitmapDecoder *bitmapdecoder = NULL;
	IWICBitmapFrameDecode  *pframe = NULL;
	pWH = new Point2D;

	//读取图片
	bitmapdecoder = NULL;
	//从内存中获取图像
	HRSRC imageResHandle = NULL;
	IWICStream *pStream = NULL;
	HGLOBAL imageResDataHandle = NULL;

	void *pImageFile = NULL;
	//读取图片
	bitmapdecoder = NULL;

	DWORD imageFileSize = 0;
	imageResHandle = FindResourceW(NULL, MAKEINTRESOURCE(filename), lpType);

	HRESULT hr = imageResHandle ? S_OK : E_FAIL;

	if (SUCCEEDED(hr))

	{

		// Load the resource.

		imageResDataHandle = LoadResource(NULL, imageResHandle);



		hr = imageResDataHandle ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))

	{

		// Lock it to get a system memory pointer.

		pImageFile = LockResource(imageResDataHandle);



		hr = pImageFile ? S_OK : E_FAIL;

	}

	if (SUCCEEDED(hr))

	{

		// Calculate the size.

		imageFileSize = SizeofResource(NULL, imageResHandle);
		hr = imageFileSize ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.

		hr = IWIIF->CreateStream(&pStream);

	}

	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	IWIIF->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &bitmapdecoder);

	if (!bitmapdecoder)
		return FALSE;
	//获取图片转换对象
	pframe = NULL;
	bitmapdecoder->GetFrame(0, &pframe);

	//初始化图片转换结构
	IWIIF->CreateFormatConverter(&fmtcovter);

	//将图片转换成D2D支持的图形模式，保存在获取到的对象中
	fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	IWICBitmapSource *IWICBS;
	IWICBS = (IWICBitmapSource*)fmtcovter;
	IWICBitmap *t_Bitmap = NULL;
	IWIIF->CreateBitmapFromSource(IWICBS, WICBitmapNoCache, &t_Bitmap);

	//获取图片宽高
	UINT t_ImageHeight;
	UINT t_ImageWidth;
	t_Bitmap->GetSize(&t_ImageWidth, &t_ImageHeight);
	pWH->rc.left = 0;
	pWH->rc.top = 0;
	pWH->rc.right = t_ImageWidth;
	pWH->rc.bottom = t_ImageHeight;

	//将转换后的图片附加到D2D的HWND中，必须为绘制用的HWND
	HRDT->CreateBitmapFromWicBitmap(fmtcovter, NULL, &pWH->Bitmap);
	//转换失败
	if (!pWH->Bitmap)
	{
		return FALSE;
	}
	//释放临时结构对象
	fmtcovter->Release();
	pframe->Release();
	bitmapdecoder->Release();
	return TRUE;
}



BOOL MyToolSet::MyLoadImageFromStream(CONST WCHAR *filename, Point2D *&pWH)
{
	//初始化临时结构变量
	IWICFormatConverter * fmtcovter = NULL;
	IWICBitmapDecoder *bitmapdecoder = NULL;
	IWICBitmapFrameDecode  *pframe = NULL;

	pWH = new Point2D;

	//读取图片
	bitmapdecoder = NULL;
	char *Original_Arr;
	FILE *Original;
	fopen_s(&Original, "1.001", "rb");
	fseek(Original, 0, SEEK_END);
	long len = ftell(Original);
	fseek(Original, 0, SEEK_SET);
	Original_Arr = (char *)malloc(1300000000 * sizeof(char));
	fread(Original_Arr, len, 1, Original);

	IWICStream *pStream = NULL;
	IWIIF->CreateStream(&pStream);
	pStream->InitializeFromMemory(

		reinterpret_cast<BYTE*>(Original_Arr),

		len

	);
	IWIIF->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &bitmapdecoder);

	if (!bitmapdecoder)
		return FALSE;

	pframe = NULL;
	bitmapdecoder->GetFrame(0, &pframe);

	IWIIF->CreateFormatConverter(&fmtcovter);
	//将图片转换成D2D支持的图形模式，保存在获取到的对象中
	fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	IWICBitmapSource *IWICBS;
	IWICBS = (IWICBitmapSource*)fmtcovter;
	IWICBitmap *t_Bitmap = NULL;
	IWIIF->CreateBitmapFromSource(IWICBS, WICBitmapNoCache, &t_Bitmap);

	//获取图片宽高
	UINT t_ImageHeight;
	UINT t_ImageWidth;
	t_Bitmap->GetSize(&t_ImageWidth, &t_ImageHeight);
	pWH->rc.left = 0;
	pWH->rc.top = 0;
	pWH->rc.right = t_ImageWidth;
	pWH->rc.bottom = t_ImageHeight;
	//pWH->Bitmap = (Bitmap *)t_Bitmap;
	//将转换后的图片附加到D2D的HWND中，必须为绘制用的HWND
	HRDT->CreateBitmapFromWicBitmap(fmtcovter, NULL, &pWH->Bitmap);

	//转换失败
	if (!pWH->Bitmap)
	{
		return FALSE;
	}
	//释放临时结构对象
	fmtcovter->Release();
	pframe->Release();
	bitmapdecoder->Release();
	t_Bitmap->Release();
	return TRUE;
}

#endif