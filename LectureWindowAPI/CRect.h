#pragma once
#include "CObject.h"

class CRect : public CObject
{
private:
	int r;
	int angle;
public:
	CRect();
	CRect(POINT center, int r);
	~CRect();

	void Update(RECT *rectView);
	void Draw(HDC hdc) override;
	BOOL Collision(int shape) override;
};



