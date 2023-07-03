#include "CStar.h"

#define PI 3.141592
#define DegreeToRadian(degree)((degree)*PI/180)

CStar::CStar()
{
	shape = 0, point.x = 0, point.y = 0;
	speed = 10;
	r = 20;
	angle = 0;
}

CStar::CStar(POINT center, int r)
{
	point.x = center.x;
	point.y = center.y;

	srand(time(NULL));
	speed = rand() % 10 + 30;
	double theta = DegreeToRadian(rand() % 360);

	direction_x = cos(theta);
	direction_y = sin(theta);

	angle = 0;
	this->shape = 1;
	this->r = r;
}

CStar::~CStar()
{
}

void CStar::Update(RECT *rectView)
{
	if (point.x + r > rectView->right || point.x - r < rectView->left) 
	{
		direction_x = -direction_x;
	}
	else if (point.y + r > rectView->bottom || point.y - r < rectView->top)
	{
		direction_y = -direction_y;
	}
	point.x += direction_x * speed;
	point.y += direction_y * speed;
	angle += 30;
}

void CStar::Draw(HDC hdc)
{
	POINT large_point[10];
	POINT small_point[5];


	for (int i = 0; i < 5; i++)
	{
		large_point[i * 2].x = r * cos(DegreeToRadian(-36 + 72 * i)) + point.x + cos(DegreeToRadian(angle));
		large_point[i * 2].y = r * sin(DegreeToRadian(-36 + 72 * i)) + point.y + sin(DegreeToRadian(angle));
	}

	double d = sqrt(pow(large_point[0].x - large_point[2].x, 2) + pow(large_point[0].y - large_point[2].y, 2));
	double small_r = d / 2 * (tan(DegreeToRadian(54)) - tan(DegreeToRadian(36)));

	for (int i = 0; i < 5; i++)
	{
		large_point[i * 2 + 1].x = small_r * cos(DegreeToRadian(0 + 72 * i)) + point.x + cos(DegreeToRadian(angle));
		large_point[i * 2 + 1].y = small_r * sin(DegreeToRadian(0 + 72 * i)) + point.y + sin(DegreeToRadian(angle));
	}

	HPEN hPen = CreatePen(PS_NULL, 0, RGB(1, 0, 0)); // 선 없는 펜 생성
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // 생성한 펜 선택

	Polygon(hdc, large_point, 10); // 별 모양 그리기

	SelectObject(hdc, hOldPen); // 이전 펜으로 선택 복원
	DeleteObject(hPen); // 생성한 펜 삭제
}

BOOL CStar::Collision(int shape)
{
	return 0;
}
