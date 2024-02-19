// LectureWindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "LectureWindowAPI.h"

#define MAX_LOADSTRING 100
#define timer_ID_1 11 
#define timer_ID_2 123 // for ani

#pragma comment(lib, "msimg32.lib")
HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hFrontImage;
BITMAP bitFront;

HBITMAP hTransparentImage;
BITMAP bitTransparent;

HBITMAP hAniImage;
BITMAP bitAni;

const int SPRITE_SIZE_X = 57;
const int SPRITE_SIZE_Y = 52;

int RUN_FRAME_MAX = 0;
int RUN_FRAME_MIN = 0;

int curframe = RUN_FRAME_MIN;

int SPRITE_FRAME_COUNT_X = 0;
int SPRITE_FRAME_COUNT_Y = 0;

HBITMAP hDoubleBufferImage;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

// text
RECT rectView;


// Funcs
void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void UpdataFrame(HWND hWnd);
void DrawRectText(HDC hdc);

// Ÿ�̸ӿ��� �θ��� �Լ�
VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

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

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LECTUREWINDOWAPI));

	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	/*while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/

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
		200, 300, 800, 600, nullptr, nullptr, hInstance, nullptr); //szTitle , CW_USEDEFAULT, 0, CW_USEDEFAULT, 0

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
	case WM_SIZE:
		GetClientRect(hWnd, &rectView);

		break;
	case WM_CREATE: // �����찡 ������ �� �ѹ� ȣ�� (������ó��)
		CreateBitmap();
		SetTimer(hWnd, timer_ID_2, 20, AniProc);
		GetClientRect(hWnd, &rectView);
		break;
	case WM_TIMER:
		/*if (wParam == timer_ID_2)
		{
			UpdataFrame();
			InvalidateRect(hWnd, NULL, true);

		}*/
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
		//DrawBitmap(hWnd, hdc);
		DrawBitmapDoubleBuffering(hWnd, hdc);
		DrawRectText(hdc);

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

void CreateBitmap()
{
	// ����
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/rex_image.bmp"), IMAGE_BITMAP, 500, 500, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hBackImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("�̹��� �ε� ����"), _T("������������"), MB_OK);
			return;
		}
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);

	}

	//�ð�
	{
		hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hTransparentImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("�̹��� �ε� ����2"), _T("������������2"), MB_OK);
			return;
		}
		GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
	}

	//Ani
	{
		hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (hAniImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("�̹��� �ε� ����3"), _T("������������2"), MB_OK);
			return;
		}
		GetObject(hAniImage, sizeof(BITMAP), &bitAni);

		RUN_FRAME_MAX = bitAni.bmWidth / SPRITE_SIZE_X - 1;
		RUN_FRAME_MIN = 2;
		curframe = RUN_FRAME_MIN;

		SPRITE_FRAME_COUNT_X = bitAni.bmWidth / SPRITE_SIZE_X;
		SPRITE_FRAME_COUNT_Y = bitAni.bmHeight / SPRITE_SIZE_Y;

	}

	{//background ��� �갡 back ��
		hFrontImage = (HBITMAP)LoadImage(NULL, TEXT("images/Background.bmp"), IMAGE_BITMAP, 500, 500, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		if (hFrontImage == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("�̹��� �ε� ����4"), _T("������������"), MB_OK);
			return;
		}
		GetObject(hFrontImage, sizeof(BITMAP), &bitFront);
	}
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	{
		// >> : ����
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);

	}


	{// >> : �ð�
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hTransparentImage);
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		//BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY);
		TransparentBlt(hdc, 150, 150, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}

	{// >> : zero_run
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
		bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X;
		by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y;

		int xStart = curframe * bx;
		int yStart = 0;
		//BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY);
		TransparentBlt(hdc, 150, 300, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}

}

void DeleteBitmap()
{
	DeleteObject(hAniImage);
	DeleteObject(hBackImage);
	DeleteObject(hTransparentImage);
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

void DrawRectText(HDC hdc)
{

	TCHAR strTest[] = _T("�̹��� ���");
	TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));

}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
	{
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
	}
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	{
		// >> : ����
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}


	{// >> : �ð�
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransparentImage);
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		//BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY);
		TransparentBlt(hMemDC, 150, 150, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
	}

	{// >> : zero_run
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
		bx = bitAni.bmWidth / SPRITE_FRAME_COUNT_X;
		by = bitAni.bmHeight / SPRITE_FRAME_COUNT_Y;

		int xStart = curframe * bx;
		int yStart = 0;
		//BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY);

		static int xPos = 0;
		TransparentBlt(hMemDC, 150 + xPos, 300, bx, by, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));
		StretchBlt(hMemDC, 150 + xPos, 400, -bx, by, hMemDC2, xStart, yStart, bx, by, SRCCOPY);

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
	}
	// hMemDC�� �׸���
	// hdc�� �׸��� �ѹ��� �Ű��ش�

	{ // ���׸��� ���۳��� �ڿ� ���� ���̰�
		hMemDC2 = CreateCompatibleDC(hMemDC);
		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hFrontImage);
		bx = bitFront.bmWidth;
		by = bitFront.bmHeight;

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC2, hBrush);

		Ellipse(hMemDC2, 250, 100, 450, 300);
		SelectObject(hMemDC2, oldBrush);
		DeleteObject(hBrush);

		TransparentBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));
		
		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);

	}


	TransparentBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, RGB(255, 0, 255));
	//BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

}