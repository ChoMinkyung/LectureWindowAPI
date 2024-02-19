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
	void Update(RECT* rectView)override;
	void Draw(HDC hdc) override;
	BOOL Collision(std::vector<CObject*>& objects) override;
	BOOL CircleCollision(CObject* object);
	int GetR() override;
};

