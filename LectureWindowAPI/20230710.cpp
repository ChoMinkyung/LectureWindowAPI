// LectureWindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "LectureWindowAPI.h"
#include <stdio.h>
// >> : GDI+
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
// << :

#pragma comment(lib, "msimg32.lib")

#define timer_ID_2 123 // for ani

RECT rectView;

const int SPRITE_SIZE_X = 57;
const int SPRITE_SIZE_Y = 52;

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;

HBITMAP hAniImage;
BITMAP bitAni;

int curframe = RUN_FRAME_MIN;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;

void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdataFrame(HWND hWnd);

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

ULONG_PTR g_GdiToken;

void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_End();

#define MAX_LOADSTRING 100

BOOL CALLBACK Diglog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);


// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM); // ������ �޼��� �޴�, �׸� �׸��� , �̺�Ʈ �޾Ƽ� ó��
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LECTUREWINDOWAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	Gdi_Init();
	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{
		Gdi_End();
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LECTUREWINDOWAPI));

	MSG msg;


	// �⺻ �޽��� �����Դϴ�:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LECTUREWINDOWAPI));
	wcex.hCursor = LoadCursor(nullptr, IDI_HAND);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(130, 165, 113));//GetStockObject(BLACK_BRUSH);//(COLOR_WINDOW+1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LECTUREWINDOWAPI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	HWND hWnd = CreateWindowW(szWindowClass, _T("�ΰ��� ù ��° ������"), WS_OVERLAPPEDWINDOW,
		200, 300, 1000, 400, nullptr, nullptr, hInstance, nullptr); //szTitle , CW_USEDEFAULT, 0, CW_USEDEFAULT, 0

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE: // �����찡 ������ �� �ѹ� ȣ�� (������ó��)
		CreateBitmap();
		SetTimer(hWnd, timer_ID_2, 20, AniProc);
		GetClientRect(hWnd, &rectView);
		break;
		break;
	case WM_KEYDOWN: //-> ���� Ű �� : wParam
	{
	}
	break;
	case WM_KEYUP:
	{

	}
	break;

	case WM_CHAR:
	{

	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_DialogBox:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Diglog_Test1_Proc);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		//Gdi_Draw(hdc);
		DrawBitmap(hWnd, hdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteBitmap();
		KillTimer(hWnd, timer_ID_2);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL CALLBACK Diglog_Test1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int Check[3], Radio;
	TCHAR hobby[][30] = { _T("����"), _T("���ǰ���"), _T("����") };
	TCHAR sex[][30] = { _T("����"), _T("����") };
	TCHAR output[200];

	switch (iMsg)
	{

	case WM_INITDIALOG:
	{
		HWND hBtn = GetDlgItem(hDlg, IDC_BUTTON_PAUSE);
		EnableWindow(hBtn, FALSE);

		CheckRadioButton(hDlg, IDC_RADIO_FEMALE, IDC_RADIO_MALE, IDC_RADIO_FEMALE);
	}
	return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CHECK_READING:
			Check[0] = 1 - Check[0];
			break;
		case IDC_CHECK_MUSIC:
			Check[1] = 1 - Check[1];
			break;
		case IDC_CHECK_GAME:
			Check[2] = 1 - Check[2];
			break;

		case IDC_RADIO_FEMALE:
			Radio = 0;
			break;
		case IDC_RADIO_MALE:
			Radio = 1;
			break;

		case IDC_BUTTON_OUTPUT:
			_stprintf_s(output, _T("������ ��̴� %s %s %s �Դϴ�.\r\n") _T("������ ������ %s �Դϴ�."),
				Check[0] ? hobby[0] : _T(""), Check[1] ? hobby[1] : _T(""), Check[2] ? hobby[2] : _T(""),
				sex[Radio]);
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
			break;
		case IDC_BUTTON_PRINT:
		{
			HDC hdc = GetDC(hDlg);
			TextOut(hdc, 0, 0, _T("��µǾ����ϴ�."), _tcsclen(_T("��µǾ����ϴ�.")));

			SetDlgItemText(hDlg, IDC_TEXT, _T("��µǾ����ϴ�."));
			ReleaseDC(hDlg, hdc);
		}
		break;
		case IDC_BUTTON_END:
			break;
		case IDC_BUTTON_START:
		{
			HDC hdc = GetDC(hDlg);

			SetDlgItemText(hDlg, IDC_TEXT, _T("Start"));
			ReleaseDC(hDlg, hdc);

			HWND hBtn = GetDlgItem(hDlg, IDC_BUTTON_START);
			EnableWindow(hBtn, FALSE);
			hBtn = GetDlgItem(hDlg, IDC_BUTTON_PAUSE);
			EnableWindow(hBtn, TRUE);

		}
		break;
		case IDC_BUTTON_PAUSE:
		{
			HDC hdc = GetDC(hDlg);

			SetDlgItemText(hDlg, IDC_TEXT, _T("Pause"));
			ReleaseDC(hDlg, hdc);

			HWND hBtn = GetDlgItem(hDlg, IDC_BUTTON_START);
			EnableWindow(hBtn, TRUE);
			hBtn = GetDlgItem(hDlg, IDC_BUTTON_PAUSE);
			EnableWindow(hBtn, FALSE);
		}

		break;
		case IDOK:
			EndDialog(hDlg, 0);
			break;
		case IDEXIT:
			EndDialog(hDlg, 0);
			break;
		case IDC_BUTTON_COPY:
		{
			TCHAR str[100];
			GetDlgItemText(hDlg, IDC_EDIT_INPUT, str, 100);
			SetDlgItemText(hDlg, IDC_EDIT_COPY, str);
		}
		break;
		case IDC_BUTTON_CLEAR:
			SetDlgItemText(hDlg, IDC_EDIT_INPUT, _T(""));
			SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}

void Gdi_Init()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	// : text
	SolidBrush brush(Color(255, 255, 0, 0));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF pointF(10.0f, 20.0f);
	//graphics.DrawString(L"Hello GDI+!!", -1, &font, pointF, &brush);

	// : line
	Pen pen(Color(128, 255, 0, 0));
	//graphics.DrawLine(&pen, 0, 0, 200, 100);

	// : image
	Image img((WCHAR*)L"images/sigong.png");
	int w = img.GetWidth();
	int h = img.GetHeight();

	//graphics.DrawImage(&img, 300, 100, w, h);

	//>> : alpha rect
	brush.SetColor(Color(128, 255, 0, 100));
	//graphics.FillRectangle(&brush, 100, 100, 200, 300);

	// : ani
	Image img2((WCHAR*)L"images/zero_run.png");
	w = img2.GetWidth() / SPRITE_FRAME_COUNT_X;
	h = img2.GetHeight() / SPRITE_FRAME_COUNT_Y;
	int xStart = curframe * w;
	int yStart = 0;

	ImageAttributes imgAttr0;
	imgAttr0.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(&img2, Rect(200, 100, w, h), xStart, yStart, w, h, UnitPixel, &imgAttr0);


	// >> rotation
	Image* pImg = nullptr;
	pImg = Image::FromFile((WCHAR*)L"images/sigong.png");
	int xPos = 400;
	int yPos = 200;
	if (pImg)
	{
		w = pImg->GetWidth();
		h = pImg->GetHeight();

		Gdiplus::Matrix mat;
		static int rot = 0;
		mat.RotateAt((rot % 360), Gdiplus::PointF(xPos + (float)(w / 2), yPos + (float)(h / 2))
		);
		graphics.SetTransform(&mat);
		graphics.DrawImage(pImg, xPos, yPos, w, h);
		rot += 10;

		mat.Reset();
		graphics.SetTransform(&mat);
	}


	// ����
	ImageAttributes imgAttr;
	imgAttr.SetColorKey(Color(240, 0, 240), Color(260, 10, 250));
	xPos = 100;
	graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

	if (pImg)
	{
		REAL transparency = 0.5f;
		ColorMatrix colorMatrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, transparency, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		imgAttr.SetColorMatrix(&colorMatrix);
		xPos = 150;
		graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

		ColorMatrix grayMatrix = {
			0.3f, 0.3f, 0.3f, 0.0f, 0.0f,
			0.6f, 0.6f, 0.6f, 0.0f, 0.0f,
			0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		imgAttr.SetColorMatrix(&grayMatrix);
		xPos = 200;
		graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

		xPos = 250;
		pImg->RotateFlip(RotateNoneFlipX);
		graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

		delete pImg;
	}


}

void Gdi_End()
{
	GdiplusShutdown(g_GdiToken);
}

void CreateBitmap()
{
	hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hAniImage == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("�̹��� �ε� ����"), _T("������������"), MB_OK);
		return;
	}
	GetObject(hAniImage, sizeof(BITMAP), &bitAni);

	RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1;
	RUN_FRAME_MIN = 2;
	curframe = RUN_FRAME_MIN;

	SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
	SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	Gdi_Draw(hdc);
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;


	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
	bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X;
	by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y;


	int xStart = curframe * bx;
	int yStart = 0;
	//BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY);

	static int xPos = 0;
	TransparentBlt(hMemDC, 150 + xPos, 300, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));
	StretchBlt(hMemDC, 150 + xPos, 400, -bx, by, hMemDC, xStart, yStart, bx, by, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void DeleteBitmap()
{
	DeleteObject(hAniImage);
}

void UpdataFrame(HWND hWnd)
{
	curframe++;
	if (curframe > RUN_FRAME_MAX) curframe = RUN_FRAME_MIN;
	InvalidateRect(hWnd, NULL, false);
}

static int yPos = 0;

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	UpdataFrame(hWnd);

	yPos += 5;
	if (yPos > rectView.bottom) yPos = 0;
}


