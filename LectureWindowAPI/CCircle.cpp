#include "CCircle.h"

CCircle::CCircle()
{
	shape = 0, point.x = 0, point.y = 0;
	speed = 1;
	r = 20;
}

CCircle::CCircle(POINT center, int r)
{
	point.x = center.x;
	point.y = center.y;

	srand(time(NULL));
	speed = rand()%10 + 20;

	double theta = rand() % 360 * 3.141592 / 180;

	direction_x = cos(theta);
	direction_y = sin(theta);

	this->shape = 0;
	this->r = r;
}

CCircle::~CCircle()
{

}

void CCircle::Update(RECT *rectView)
{
	if (point.x + r > rectView->right || point.x - r < rectView->left) // 0, 1
	{
		direction_x = -direction_x;

	}
	else if (point.y + r> rectView->bottom  || point.y - r< rectView->top) // 1, 0
	{
		direction_y = -direction_y;
	}
	point.x += direction_x * speed;
	point.y += direction_y * speed;
}

void CCircle::Draw(HDC hdc)
{
	Ellipse(hdc, point.x - r, point.y - r, point.x + r, point.y + r);
}

BOOL CCircle::Collision(int shape)
{

	return 0;
}


BOOL CCircle::InCircleWithCircle(CCircle c)
{
	if (LengthPts(c.point) < r + c.r) return TRUE;
	else return FALSE;
}