#pragma once
#include "framework.h"
#include <vector>

struct Node
{
	int f_n; // g_n + h_n
	int g_n; // 출발에서 현재까지
	int h_n; // 현재에서 도착까지

	int open; // 0:닫힘 1:열림 2:길이 될 가능성 3:길로 선택 -1:장애물 -2:길이 아님
	bool start; // 시작점인지 아닌지
	bool end; // 도착점인지 아닌지

	POINT point;
	Node* parent;
	Node* child;
};

class AstarNode
{
private:
	std::vector<std::vector<Node*>> node;
	std::vector<Node*> block;
	int end_x, end_y;
	int start_x, start_y;
public:
	AstarNode();
	AstarNode(int numRows, int numCols);
	~AstarNode();
	void Draw(HDC hdc);
	void Draw_Rect(HDC hdc, int height, int width);

	int FindMin();
	void Update(int x, int y);
	void Cal(int current_x, int current_y, int parent_x, int parent_y);
	void FindWay();

	int InRect(POINT ptMousePos ,int startEndSelect);
	void Reset();

	RECT* Move(HDC hdc, int call);
};

