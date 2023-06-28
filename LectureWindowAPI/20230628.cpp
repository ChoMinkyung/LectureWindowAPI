// LectureWindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "LectureWindowAPI.h"

#define MAX_LOADSTRING 100

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
		200, 300, 600, 400, nullptr, nullptr, hInstance, nullptr); //szTitle , CW_USEDEFAULT, 0, CW_USEDEFAULT, 0

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
	static TCHAR str[100];
	static int count, yPos;

	switch (message)
	{
	case WM_CREATE: // �����찡 ������ �� �ѹ� ȣ�� (������ó��)
		count = 0;
		yPos = 100;
		break;
	case WM_KEYDOWN: //-> ���� Ű �� : wParam
	{
		int breakpoint = 9999;
	}
	break;
	case WM_KEYUP:
	{
		int breakpoint = 9999;

	}
	break;

	case WM_CHAR:
	{
		if (wParam == VK_BACK && count > 0)
		{
			count--;
		}
		else if (wParam == VK_RETURN)
		{
			yPos += 20;
		}
		else
		{
			str[count++] = wParam;
		}
		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE);
		/*
		str[count++] = wParam;
		str[count] = NULL;
		//InvalidateRect()
		InvalidateRgn(hWnd, NULL, TRUE); // TRUE : �����ٰ� �ٽ� �׸��� FALSE�� ������
		*/

		//HDC hdc = GetDC(hWnd);
		//LPCWSTR str = (LPCWSTR)_T("Ű ���ȴ�!!!!");
		//TextOut(hdc, 300, 120, str, _tcslen(str));
		//ReleaseDC(hWnd, hdc);
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
		//TextOut(hdc, 100, yPos, str, _tcslen(str));

		/*TextOut(hdc, 100, 100, _T("Hello world!!"), _tcslen(_T("Hello world!")));

		RECT rect = { 300, 400, 300, 550 };

		rect.left = 200;
		rect.right = 312;
		rect.top = 10;
		rect.bottom = 100;
		SetTextColor(hdc, RGB(0, 200, 100));
		DrawText(hdc, _T("Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!"),
			_tcslen(_T("Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!Hello World!")), &rect, DT_WORDBREAK |DT_NOCLIP | DT_CENTER | DT_VCENTER);*/

			/* ��Ʈ�� ���! release�� ����� ��
			HDC memDC = GetDC(hWnd);
			ReleaseDC(hWnd, memDC);
			*/

		////line
		//MoveToEx(hdc, 100, 100, NULL);
		//LineTo(hdc, 500, 500);

		////one
		//Ellipse(hdc, 400, 0, 500, 100);

		//rect

		HPEN hPen, oldPen;
		hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 255));
		oldPen = (HPEN)SelectObject(hdc, hPen);

		HBRUSH hBrush, oldBrush;
		//hBrush = CreateSolidBrush(RGB(235, 235, 0));
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);


		Rectangle(hdc, 0, 0, 40, 40);

		POINT point[10] = { {10, 150}, {250, 30}, {500, 150}, {350, 300}, {150, 300} };

		Polygon(hdc, point, 5);

		SelectObject(hdc, oldPen);
		DeleteObject(hPen);

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
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
