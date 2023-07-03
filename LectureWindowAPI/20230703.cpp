// LectureWindowAPI.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
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
	static RECT rectView; //������ ũ�� ���
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
	case WM_CREATE: // �����찡 ������ �� �ѹ� ȣ�� (������ó��)
		bFlag = false;
		count = 0;
		SetTimer(hWnd, 1, 70, NULL);
		GetClientRect(hWnd, &rectView);
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
		InvalidateRgn(hWnd, NULL, TRUE);

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
		case ID_DRAW_CIRCLE:
		{

			int temp = type;
			int ans = MessageBox(hWnd, _T("�� �׸���?"), _T("���� ����"), MB_YESNOCANCEL);
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
				_stprintf(str, _T("%s ������ ���ڽ��ϱ�?"), ofn.lpstrFile);
				ans = MessageBox(hWnd, str, _T("���� ����"), MB_OK);
				if (ans == IDOK)
				{
					OutFromFile(ofn.lpstrFile, hWnd);
					//_tcscpy(buffer, OutFromFile(ofn.lpstrFile, hWnd));
				}
			}
		/*	else
			{
				TCHAR str[100];
				_stprintf(str, _T("%s ������ �� �� �����ϴ�."), ofn.lpstrFile);
				MessageBox(hWnd, str, _T("Ȯ��"), MB_OK);
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
		InvalidateRect(hWnd, NULL, TRUE); // ����� �ٽ� �׷���
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
