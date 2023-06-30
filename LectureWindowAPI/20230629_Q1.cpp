// LectureWindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "LectureWindowAPI.h"
#include <windows.h>

#define MAX_LOADSTRING 100

void DrawRect(HDC hdc, BOOLEAN key, int loc)
{
	HBRUSH hBrush, oldBrush;
	int r = 255, g = 255, b = 255;

	if (key && loc == 1)
		g = b = 0;
	else g = b = 255;

	hBrush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 200, 20, 300, 120); // 위

	SetBkColor(hdc, RGB(r, g, b));
	TextOut(hdc, 230, 50, _T("위쪽"), _tcslen(_T("위쪽")));


	if (key && loc == 2)
		g = b = 0;
	else g = b = 255;

	hBrush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 200, 220, 300, 320); // 아래

	SetBkColor(hdc, RGB(r, g, b));
	TextOut(hdc, 230, 250, _T("아래쪽"), _tcslen(_T("아래쪽")));


	if (key && loc == 3)
		g = b = 0;
	else g = b = 255;

	hBrush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 300, 120, 400, 220); // 우

	SetBkColor(hdc, RGB(r, g, b));
	TextOut(hdc, 320, 150, _T("오른쪽"), _tcslen(_T("오른쪽")));

	if (key && loc == 4)
		g = b = 0;
	else g = b = 255;

	hBrush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 100, 120, 200, 220); // 좌

	SetBkColor(hdc, RGB(r, g, b));
	TextOut(hdc, 120, 150, _T("왼쪽"), _tcslen(_T("왼쪽")));


	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 200, 120, 300, 220); // 중간

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);


	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

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

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
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
	static TCHAR str[100];
	static int count, yPos;
	static BOOLEAN key;
	static int loc;

	switch (message)
	{
	case WM_CREATE: // 윈도우가 생성될 때 한번 호출 (생성자처럼)
		count = 0;
		yPos = 100;
		key = false;
		loc = 0;
		break;
	case WM_KEYDOWN: //-> 가상 키 값 : wParam
	{
		key = true;

		if (wParam == VK_UP && key)
		{
			loc = 1;
		}
		else if (wParam == VK_DOWN && key)
		{
			loc = 2;
		}
		else if (wParam == VK_RIGHT && key)
		{
			loc = 3;
		}
		else if (wParam == VK_LEFT && key)
		{
			loc = 4;
		}
		InvalidateRgn(hWnd, NULL, TRUE);

	}
	break;
	case WM_KEYUP:
	{
		key = false;
		InvalidateRgn(hWnd, NULL, TRUE);
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
		DrawRect(hdc, key, loc);

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
