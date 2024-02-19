#include "framework.h"
#include "CRect.h"

#define PI 3.141592
#define DegreeToRadian(degree)((degree)*PI/180)

CRect::CRect()
{
	shape = 1, point.x = 0, point.y = 0;
	speed = 10;
	r = 20;
	angle = 0;
}

CRect::CRect(POINT center, int r)
{
	point.x = center.x;
	point.y = center.y;

	srand(time(NULL));
	speed = rand() % 10 + 30;
	double theta = DegreeToRadian(rand() % 360);

	direction_x = cos(theta);
	direction_y = sin(theta);

	angle = 0;
	shape = 1;
	this->r = r;
}

CRect::~CRect()
{
}

void CRect::Update(RECT *rectView)
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
	angle+=30;

}

void CRect::Draw(HDC hdc)
{
	POINT rect_point[4];

	for (int i = 0; i < 4; i++)
	{
		double temp = DegreeToRadian(angle + 90 * i);

		rect_point[i].x = point.x + r * cos(temp);
		rect_point[i].y = point.y + r * sin(temp);
	}

	Polygon(hdc, rect_point, 4);
}

BOOL CRect::Collision(std::vector<CObject*>& objects)
{
	return 0;
}

int CRect::GetR()
{
	return r;
}
