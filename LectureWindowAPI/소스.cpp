// WindowsProject1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "LectureWindowAPI.h"
#include <cmath>
#include <ctime>

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawCircle(HDC hdc, POINT center, int r);
void DrawStar(HDC hdc, POINT center, int r);
void DrawRectangle(HDC hdc, POINT center, int d);

#define PI 3.141592
#define degreeToRadian(degree) ((degree) * PI / 180)

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_LECTUREWINDOWAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(204, 204, 255));
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		200, 200, 1024, 768, nullptr, nullptr, hInstance, nullptr);

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


#define timer_ID_1 11
#define timer_ID_2 22
const int circleRadius = 50;

double LengthPts(POINT pt1, POINT pt2)
{
	return (sqrt(
		(float)(pt2.x - pt1.x) * (pt2.x - pt1.x) +
		(float)(pt2.y - pt1.y) * (pt2.y - pt1.y)));
}

BOOL InCircle(POINT pt1, POINT pt2)
{
	if (LengthPts(pt1, pt2) < circleRadius) return TRUE;
	else return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT ptCurPos;
	static POINT ptMousePos;
	static RECT rectView;

	static bool bFlag;


	switch (message)
	{
	case WM_CREATE:
		ptCurPos.x = 20;
		ptCurPos.y = 20;
		bFlag = false;
		GetClientRect(hWnd, &rectView);
		//SetTimer(hWnd, timer_ID_1, 500, NULL); 
		//SetTimer(hWnd, timer_ID_2, 1000, NULL); // 1000 = 1�� ����
		break;

	case WM_TIMER:
		if (wParam == timer_ID_1)
		{
			ptMousePos.x += 20;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (wParam == timer_ID_2)
		{
			ptMousePos.y += 20;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_KEYDOWN: //Ű���� ������ ��
	{
		int breakpoint = 999;
	}
	break;

	case WM_KEYUP:
	{
		int breakpoint = 999;
	}
	break;

	case WM_CHAR:
	{
		int breakpoint = 999;

		//InvalidateRgn(hWnd, NULL, TRUE); //���� �����������, false = �Ϻκи� ������
	}
	break;
	case WM_LBUTTONDOWN:
	{
		bFlag = true;
		ptMousePos.x = LOWORD(lParam);
		ptMousePos.y = HIWORD(lParam);
		InvalidateRgn(hWnd, NULL, FALSE);
	}
	break;

	case WM_LBUTTONUP:
	{
		InvalidateRgn(hWnd, NULL, FALSE);
	}
	break;

	case WM_MOUSEMOVE:
		if (!bFlag)
		{
			ptCurPos.x = LOWORD(lParam);
			ptCurPos.y = HIWORD(lParam);
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

		srand(time(NULL));

		if (bFlag)
		{
			int a = rand() % 3;

			switch (a)
			{
			case 0:
				DrawRectangle(hdc, ptMousePos, 50);
				break;
			case 1:
				DrawCircle(hdc, ptMousePos, 50);
				break;
			case 2:
				DrawStar(hdc, ptMousePos, 50);
				break;
			}

		}

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_COMMAND: //�޴��� �������� �� �߻��ϴ� �̺�Ʈ
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

	case WM_DESTROY:
		KillTimer(hWnd, timer_ID_1);
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

void DrawGrid(HDC hdc, POINT center, int Width, int Height, int Count)
{
	int a = Width / Count;
	int b = Height / Count;

	for (int i = 0; i <= Width; i += a)
	{
		MoveToEx(hdc, center.x - Width / 2 + i, center.y - Height / 2, NULL);
		LineTo(hdc, center.x - Width / 2 + i, center.y + Height / 2);
	}
	for (int j = 0; j <= Height; j += b)
	{
		MoveToEx(hdc, center.x - Width / 2, center.y - Height / 2 + j, NULL);
		LineTo(hdc, center.x + Width / 2, center.y - Height / 2 + j);
	}
}

void DrawRectangle(HDC hdc, POINT center, int d)
{
	Rectangle(hdc, center.x - d, center.y - d, center.x + d, center.y + d);
}

void DrawCircle(HDC hdc, POINT center, int r)
{
	//if (bFlag)
	   //SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
	Ellipse(hdc, center.x - r, center.y - r, center.x + r, center.y + r);
}

void DrawStar(HDC hdc, POINT center, int r)
{
	POINT point[10];
	double theta = degreeToRadian(360 / 5);

	for (int i = 0; i < 5; i++)
	{
		point[2 * i].x = r * cos(theta * i) + center.x;
		point[2 * i].y = r * sin(theta * i) + center.y;
	}

	for (int i = 0; i < 5; i++)
	{
		point[2 * i + 1].x = r / 2 * cos(theta / 2 + theta * i) + center.x;
		point[2 * i + 1].y = r / 2 * sin(theta / 2 + theta * i) + center.y;

	}

	Polygon(hdc, point, 10);
}

/*
Q2. 1. Ŭ���̾�Ʈ ������ ���콺�� Ŭ��, �� ��ġ�� �� ����
	  1.1 �������� �簢�� , ��, ���� �����ǵ��� �Ѵ�.

   2. ������ �������� �̵� / �� Ŭ���̾�Ʈ �ܰ������� �ݻ�

   3. Ŭ������ ����
	  �簢�� / ���� ���� ������ �۵��ϵ��� �Ѵ�.

   4. �ٸ� ������Ʈ���� ���� ����
	 ��� ���� 1�� �ݻ�, 2�� ��ü, 3�� �п��� Ű ����
	 4.1 �ݻ� - �ٸ� ������Ʈ�� �ε����� ƨ���
	 4.2 ��ü - �� ���迡 ���� �ٸ� ������Ʈ�� ������ ��ü�ؼ� Ŀ���� �ϱ�
	 4.3 �п� - �� ���迡 ���� �ٸ� ������Ʈ�� ������ �п��ؼ� �۾����� �ϱ�
		�� > �� > �簢�� > ��

   5. ���� ũ�� �̻�, �Ǵ� ���ϴ� ��������� �Ѵ�.

   6.  �� ������Ʈ�� ȸ�� ��Ų��.

	  CObject
	  {
	  protected:
		 ��ǥ
		 �̵� ���ǵ�
		 �̵� ����
		 Ÿ�� ( ��, ��, �簢�� )
	  public:
		 virtual void Update() = 0;
		 virtual void Draw() = 0; (�ڱ� �ڽ��� �׷��ִ� ��)
		 virtual BOOL collision() = 0;
		 // : �׿� �Լ�
	  };

	  CCircle : public CObject
	  {
	  private:
		 ������
	  public:
		 setradius
		 void Update() override;
		 void Draw() override;
		 BOOL collision() override;
	  }
*/