// LectureWindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include "LectureWindowAPI.h"
#include <cmath>
#include <vector>
#include <commdlg.h>
#include <stdio.h>

#include "CObject.h"
#include "CCircle.h"
#include "CRect.h"
#include "CStar.h"

#define MAX_LOADSTRING 100

void OutFromFile(TCHAR filename[], HWND hWnd)
{
	FILE* fPtr;
	HDC hdc;
	int line;
	TCHAR buffer[500];
	line = 0;
	hdc = GetDC(hWnd);
#ifdef _UNICODE
	_tfopen_s(&fPtr, filename, _T("r, ccs=UNICODE"));
#else 
	_tfopen_s(&fPtr, filename, _T("r"));
#endif
	while (_fgetts(buffer, 100, fPtr) != NULL)
	{
		if (buffer[_tcslen(buffer) - 1] == _T('\n'))
			buffer[_tcslen(buffer) - 1] = NULL;
		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		line++;
	}
	                       
	fclose(fPtr);
	ReleaseDC(hWnd, hdc);
}

void Chat()
{
	/*for (int i = 0; i < 10; i++)
	{
		TextOut(hdc, 100, yPos - 20 * (line - i), str[i], _tcslen(str[i]));
		GetTextExtentPoint(hdc, str[i], _tcslen(str[i]), &size);
		SetCaretPos(100 + size.cx, yPos);
	}

	TextOut(hdc, 100, yPos, str[10], _tcslen(str[10]));*/
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
	static RECT rectView; //윈도우 크기 담기
	static POINT ptMousePos;
	static BOOL bFlag;

	static int count;
	enum { CIRCLE, RECT, STAR, CLEAR, NONE };

	static int type = NONE;
	static std::vector<CObject*> objects;
	static CObject* obj;
	HDC hdc;
	//static TCHAR buffer[500];

	switch (message)
	{
	case WM_CREATE: // 윈도우가 생성될 때 한번 호출 (생성자처럼)
		bFlag = false;
		count = 0;
		SetTimer(hWnd, 1, 70, NULL);
		GetClientRect(hWnd, &rectView);
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
		InvalidateRgn(hWnd, NULL, TRUE);

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
		case ID_DRAW_CIRCLE:
		{

			int temp = type;
			int ans = MessageBox(hWnd, _T("원 그릴래?"), _T("도형 선택"), MB_YESNOCANCEL);
			if (ans == IDYES)
			{
				type = CIRCLE;
			}
			else if (ans == IDNO)
			{
				type = NONE;
			}
			else
			{
				type = temp;
			}
		}
		break;
		case ID_DRAW_RECT:
			type = RECT;
			break;

		case ID_DRAW_STAR:
			type = STAR;
			break;
		case ID_CLEAR:
			type = NONE;
			objects.clear();
			break;
		case ID_FILEOPEN:
		{
			TCHAR filter[] = _T("Every file(*.*) \0*.*\0Text file\0*.txt;*.doc\0");
			TCHAR lpstrFile[100] = _T("");

			OPENFILENAME ofn;
			memset(&ofn, 0, sizeof(OPENFILENAME));

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = filter;
			ofn.lpstrFile = lpstrFile;
			ofn.nMaxFile = 256;
			ofn.lpstrInitialDir = _T(".");
			int ans = 0;

			if (GetOpenFileName(&ofn) != 0)
			{
				TCHAR str[100];
				_stprintf(str, _T("%s 파일을 열겠습니까?"), ofn.lpstrFile);
				ans = MessageBox(hWnd, str, _T("파일 열기"), MB_OK);
				if (ans == IDOK)
				{
					OutFromFile(ofn.lpstrFile, hWnd);
					//_tcscpy(buffer, OutFromFile(ofn.lpstrFile, hWnd));
				}
			}
		/*	else
			{
				TCHAR str[100];
				_stprintf(str, _T("%s 파일을 열 수 없습니다."), ofn.lpstrFile);
				MessageBox(hWnd, str, _T("확인"), MB_OK);
			}*/
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_LBUTTONDOWN:
	{
		ptMousePos.x = LOWORD(lParam);
		ptMousePos.y = HIWORD(lParam);
		srand(time(NULL));
		//int type = rand() % 3;

		switch (type)
		{
		case CIRCLE:
			obj = new CCircle(ptMousePos, rand() % 20 + 20);
			break;
		case RECT:
			obj = new CRect(ptMousePos, rand() % 20 + 20);
			break;
		case STAR:
			obj = new CStar(ptMousePos, rand() % 20 + 20);
			break;
		}

		objects.push_back(obj);
		InvalidateRect(hWnd, NULL, TRUE); // 지우고 다시 그려줘
	}


	break;
	case WM_LBUTTONUP:

		break;

	case WM_TIMER:

		for (auto e : objects)
		{
			e->Update(&rectView);
		}
		//InvalidateRect(hWnd, NULL, TRUE);

		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		switch (type)
		{
		case CIRCLE:
			TextOut(hdc, 50, 50, _T("MODE : CIRCLE"), _tcslen(_T("MODE : CIRCLE")));
			break;
		case RECT:
			TextOut(hdc, 50, 50, _T("MODE : RECT"), _tcslen(_T("MODE : RECT")));
			break;
		case STAR:
			TextOut(hdc, 50, 50, _T("MODE : STAR"), _tcslen(_T("MODE : STAR")));
			break;
		}

		//TextOut(hdc, 50, 50, buffer, _tcslen(buffer));

		for (auto e : objects)
		{
			e->Draw(hdc);
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
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
