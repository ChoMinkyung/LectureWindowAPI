#pragma once

#include "framework.h"
#include "CObject.h"

class CCircle : public CObject
{
private:
	int r;
public:
	CCircle();
	CCircle(POINT center, int r);
	~CCircle();
	void Update(RECT* rectView);
	void Draw(HDC hdc) override;
	BOOL Collision(int shape) override;
	BOOL InCircleWithCircle(CCircle c);
};

