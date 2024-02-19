#pragma once
#include "CObject.h"

class CStar : public CObject
{
private:
	int r;
	int angle;
public:
	CStar();
	CStar(POINT center, int r);
	~CStar();

	void Update(RECT *rectView);
	void Draw(HDC hdc) override;
	BOOL Collision(CObject* object) override;
	int GetR()override;
};

