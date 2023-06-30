#pragma once
#include "framework.h"
#include <time.h>
#include <cmath>
#include <vector>

class CObject
{
protected:
	POINT point;
	double speed;
	double direction_x;
	double direction_y;
	int shape; // 0 원 1 사각형 2 별
public:
	virtual void Update(RECT *rectView) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual BOOL Collision(int shape) = 0;
	double LengthPts(POINT pt);
};


inline double CObject :: LengthPts(POINT pt)
{
	return sqrt((float)(point.x - pt.x) * (float)(point.x - pt.x) + (float)(pt.y - point.y) * (float)(pt.y - point.y));
}