// LectureWindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "LectureWindowAPI.h"


#include <cmath>
#include <vector>

#define MAX_LOADSTRING 100

const int circleR = 30;

double LengthPts(POINT pt1, POINT pt2)
{
	return sqrt((float)(pt2.x - pt1.x) * (float)(pt2.x - pt1.x) + (float)(pt2.y - pt1.y) * (float)(pt2.y - pt1.y));
}

BOOL InCircle(POINT pt1, POINT pt2)
{
	if (LengthPts(pt1, pt2) < circleR) return TRUE;
	else return FALSE;
}

void DrawCircle(HDC hdc, POINT center, int r, BOOL bFlag)
{
	if (bFlag)
		SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));

	double x1 = center.x - r;
	double y1 = center.y - r;
	double x2 = center.x + r;
	double y2 = center.y + r;

	Ellipse(hdc, x1, y1, x2, y2);
}

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
	//static TCHAR str[100];
	//static int count, yPos;

	static POINT ptCurPos;
	static RECT rectView; //������ ũ�� ���
	static POINT ptMousePos;

	static HMENU hMenu, hSubMenu;
	static BOOL Copy;
	static BOOL bFlag;

	switch (message)
	{
	case WM_CREATE: // �����찡 ������ �� �ѹ� ȣ�� (������ó��)
		ptCurPos.x = 40;
		ptCurPos.y = 40;

		GetClientRect(hWnd, &rectView); // ���� ������ ũ�� ������
		Copy = FALSE;
		hMenu = GetMenu(hWnd);
		hSubMenu = GetSubMenu(hMenu, 2);
		EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
		EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);
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
		if (wParam == 'C' || wParam == 'c')
		{
			UINT state = GetMenuState(hSubMenu, ID_EDITCOPY, MF_BYCOMMAND);
			if (state & MF_DISABLED || state & MF_GRAYED)
			{
				EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_ENABLED);
			}
			else if (state == MF_ENABLED)
			{
				EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
			}
		}
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
		case ID_EDITCOPY:
			Copy = TRUE;
			InvalidateRect(hWnd, NULL, TRUE);

			break;
		case ID_EDITPASTE:
			Copy = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_LBUTTONDOWN:
		ptMousePos.x = LOWORD(lParam);
		ptMousePos.y = HIWORD(lParam);
		if (InCircle(ptMousePos, ptCurPos)) bFlag = TRUE;
		else bFlag = FALSE;
		InvalidateRect(hWnd, NULL, TRUE); // ����� �ٽ� �׷���

		break;
	case WM_LBUTTONUP:
		bFlag = FALSE;
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_MOUSEMOVE: // �갡 ���۵Ǹ� ��� �̺�Ʈ�� �ޱ� ������ ���콺�� ������ ���� �۵��ϵ���
		if (bFlag)
		{
			ptCurPos.x = LOWORD(lParam);
			ptCurPos.y = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, TRUE); // ����� �ٽ� �׷���
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (Copy)
		{
			TextOut(hdc, 100, 100, _T("copy ����"), _tcsclen(_T("copy ����")));
			EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
			EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_ENABLED);
		}
		else
		{
			EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_ENABLED);
			EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);
		}

		DrawCircle(hdc, ptCurPos, circleR, bFlag);

		//if (bFlag) Rectangle(hdc, ptCurPos.x - circleR, ptCurPos.y - circleR, ptCurPos.x + circleR, ptCurPos.y + circleR);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
		break;
	case WM_DESTROY:
		//KillTimer(hWnd, timer_ID_1);
		PostQuitMessage(0);

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
