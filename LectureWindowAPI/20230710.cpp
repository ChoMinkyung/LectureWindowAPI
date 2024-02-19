// LectureWindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
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


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM); // 윈도우 메세지 받는, 그림 그리고 , 이벤트 받아서 처리
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LECTUREWINDOWAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	Gdi_Init();
	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		Gdi_End();
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LECTUREWINDOWAPI));

	MSG msg;


	// 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, _T("민경의 첫 번째 윈도우"), WS_OVERLAPPEDWINDOW,
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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE: // 윈도우가 생성될 때 한번 호출 (생성자처럼)
		CreateBitmap();
		SetTimer(hWnd, timer_ID_2, 20, AniProc);
		GetClientRect(hWnd, &rectView);
		break;
		break;
	case WM_KEYDOWN: //-> 가상 키 값 : wParam
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
		// 메뉴 선택을 구문 분석합니다:
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
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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

// 정보 대화 상자의 메시지 처리기입니다.
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
	TCHAR hobby[][30] = { _T("독서"), _T("음악감상"), _T("게임") };
	TCHAR sex[][30] = { _T("여성"), _T("남성") };
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
			_stprintf_s(output, _T("선택한 취미는 %s %s %s 입니다.\r\n") _T("선택한 성별은 %s 입니다."),
				Check[0] ? hobby[0] : _T(""), Check[1] ? hobby[1] : _T(""), Check[2] ? hobby[2] : _T(""),
				sex[Radio]);
			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
			break;
		case IDC_BUTTON_PRINT:
		{
			HDC hdc = GetDC(hDlg);
			TextOut(hdc, 0, 0, _T("출력되었습니다."), _tcsclen(_T("출력되었습니다.")));

			SetDlgItemText(hDlg, IDC_TEXT, _T("출력되었습니다."));
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


	// 원본
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
		MessageBox(NULL, _T("이미지 로드 에러"), _T("에러에러에러"), MB_OK);
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


