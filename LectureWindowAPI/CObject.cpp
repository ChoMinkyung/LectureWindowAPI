#include "CObject.h"

double CObject::LengthPts(POINT pt1, POINT pt2)
{

	return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

POINT CObject::GetPoint()
{
	return point;
}

int CObject::GetShape()
{
	return shape;
}

cRGB CObject::GetRGB()
{
	return rgb;
}

void CObject::SetRGB(int r, int g, int b)
{
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

void CObject::SetCollision(BOOL collision)
{
	this->collision = collision;
}
