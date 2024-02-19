#include "CCircle.h"

CCircle::CCircle()
{
	shape = 0, point.x = 0, point.y = 0;
	speed = 1;
	r = 20;
	rgb.r = rgb.g = rgb.b = 255;
}

CCircle::CCircle(POINT center, int r)
{
	point.x = center.x;
	point.y = center.y;

	srand(time(NULL));
	speed = rand() % 10 + 10;

	double theta = rand() % 360 * 3.141592 / 180;

	direction_x = cos(theta);
	direction_y = sin(theta);

	shape = 0;
	this->r = r;
	rgb.r = rgb.g = rgb.b = 255;
}

CCircle::~CCircle()
{

}

void CCircle::Update(RECT* rectView)
{
	if (point.x + r > rectView->right || point.x - r < rectView->left) // 0, 1
	{
		direction_x = -direction_x;

	}
	else if (point.y + r > rectView->bottom || point.y - r < rectView->top) // 1, 0
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

BOOL CCircle::Collision(std::vector<CObject*> &object)
{
	for (int i = 0; i < object.size(); i++)
	{
		for (int j = i + 1; j < object.size(); j++)
		{
			if (object[i]->CircleCollision(object[j]))
			{
				printf("%d와 %d 충돌\n", i, j);
				objects[i]->SetRGB(255, 92, 33);
				objects[i]->SetCollision(TRUE);
				objects[j]->SetRGB(255, 92, 33);
				objects[j]->SetCollision(TRUE);
			}

		}
	}

	return 0;
}

BOOL CCircle::CircleCollision(CObject* object)
{
	switch (object->GetShape())
	{
	case 0: // 원이랑 충돌
		if (LengthPts(point, object->GetPoint()) < r + object->GetR()) return true;
		else return false;
		break;

	default:
		break;
	}
	return 0;
}

int CCircle::GetR()
{
	return r;
}
