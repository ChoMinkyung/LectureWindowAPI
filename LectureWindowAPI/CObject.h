#pragma once
#include "framework.h"
#include <time.h>
#include <cmath>
#include <vector>

struct cRGB
{
	int r, g, b;
};

class CObject
{
protected:
	POINT point;
	double speed;
	double direction_x;
	double direction_y;
	int shape; // 0 원 1 사각형 2 별
	cRGB rgb;
	BOOL collision = FALSE;
public:
	virtual void Update(RECT *rectView) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual BOOL Collision(std::vector<CObject*>& objects) = 0;
	virtual int GetR() = 0;
	double LengthPts(POINT pt1, POINT pt2);
	POINT GetPoint();
	int GetShape();
	cRGB GetRGB();
	void SetRGB(int r, int g, int b);
	void SetCollision(BOOL collision);
};
