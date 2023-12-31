// LectureWindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "LectureWindowAPI.h"

#define MAX_LOADSTRING 100

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

	switch (message)
	{
	case WM_CREATE: // 윈도우가 생성될 때 한번 호출 (생성자처럼)
		count = 0;
		yPos = 100;
		break;
	case WM_KEYDOWN: //-> 가상 키 값 : wParam
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
		InvalidateRgn(hWnd, NULL, TRUE); // TRUE : 지웠다가 다시 그리기 FALSE는 안지움
		*/

		//HDC hdc = GetDC(hWnd);
		//LPCWSTR str = (LPCWSTR)_T("키 눌렸다!!!!");
		//TextOut(hdc, 300, 120, str, _tcslen(str));
		//ReleaseDC(hWnd, hdc);
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

			/* 세트로 사용! release로 놔줘야 함
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
