#pragma once
#include "framework.h"
#include <vector>

struct Node
{
	int f_n; // g_n + h_n
	int g_n; // ��߿��� �������
	int h_n; // ���翡�� ��������

	int open; // 0:���� 1:���� 2:���� �� ���ɼ� 3:��� ���� -1:��ֹ� -2:���� �ƴ�
	bool start; // ���������� �ƴ���
	bool end; // ���������� �ƴ���

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

