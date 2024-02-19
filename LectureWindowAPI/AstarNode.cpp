#include "AstarNode.h"
#include <iostream>
#include<string>
#include<math.h>
using namespace std;

AstarNode::AstarNode()
{
}

AstarNode::AstarNode(int numRows, int numCols)
{
	node = std::vector<std::vector<Node*>>(numRows, std::vector<Node*>(numCols, nullptr));
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			node[i][j] = new Node();
			node[i][j]->f_n = node[i][j]->g_n = node[i][j]->h_n = 0;
			node[i][j]->open = 0;
			node[i][j]->start = false;
			node[i][j]->end = false;
			node[i][j]->parent = nullptr;
			node[i][j]->child = nullptr;
			node[i][j]->point = { i, j };
		}
	}

	//Àå¾Ö¹°
	block.push_back(node[3][4]);
	block.push_back(node[4][4]);
	block.push_back(node[5][4]);
	block.push_back(node[4][5]);

	for (auto e : block)
	{
		e->open = -1;
	}
}

AstarNode::~AstarNode()
{
	for (int i = 0; i < node.size(); i++)
	{
		for (int j = 0; j < node[i].size(); j++)
		{
			delete node[i][j];
		}
	}
}

void AstarNode::Draw(HDC hdc)
{
	for (int i = 0; i < node.size(); i++)
	{
		for (int j = 0; j < node[0].size(); j++)
		{
			Draw_Rect(hdc, i, j);
		}
	}
}

void AstarNode::Draw_Rect(HDC hdc, int height, int width)
{
	if (node[height][width]->open == 0)SelectObject(hdc, CreateSolidBrush(RGB(200, 200, 200)));
	else if (node[height][width]->open == 1) SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
	else if (node[height][width]->open == 2)SelectObject(hdc, CreateSolidBrush(RGB(212, 240, 240)));
	else if (node[height][width]->open == 3)SelectObject(hdc, CreateSolidBrush(RGB(255, 204, 102)));
	else if (node[height][width]->open == -1)SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
	else if (node[height][width]->open == -2)SelectObject(hdc, CreateSolidBrush(RGB(255, 102, 102)));

	if (node[height][width]->start) SelectObject(hdc, CreateSolidBrush(RGB(0, 102, 51)));
	if (node[height][width]->end) SelectObject(hdc, CreateSolidBrush(RGB(255, 51, 0)));
	Rectangle(hdc, 0 + width * 100, 0 + height * 100, 100 + width * 100, 100 + height * 100);

	if (node[height][width]->open > 0 || node[height][width]->open == -2)
	{
		TCHAR str[128];
		wsprintf(str, TEXT("%d"), node[height][width]->f_n);
		TextOut(hdc, 45 + 100 * width, 65 + 100 * height, str, lstrlen(str));

		wsprintf(str, TEXT("%d"), node[height][width]->g_n);
		TextOut(hdc, 25 + 100 * width, 25 + 100 * height, str, lstrlen(str));

		wsprintf(str, TEXT("%d"), node[height][width]->h_n);
		TextOut(hdc, 65 + 100 * width, 25 + 100 * height, str, lstrlen(str));
	}

}



int AstarNode::FindMin()
{
	int min = 1000;
	int min_x, min_y;

	for (int i = 0; i < node.size(); i++)
	{
		for (int j = 0; j < node[i].size(); j++)
		{
			if (node[i][j]->open == 1)
			{
				if (min > node[i][j]->f_n)
				{
					min = node[i][j]->f_n;
					min_x = i;
					min_y = j;
				}
				else if (min == node[i][j]->f_n)
				{
					if (node[i][j]->g_n < node[min_x][min_y]->g_n)
					{
						//node[min_x][min_y]->g_n
						min_x = i;
						min_y = j;
					}
				}
			}
		}
	}

	if (min == 1000) Update(start_x, start_y);
	else
	{
		if (min_x == end_x && min_y == end_y)
		{
			FindWay();
			return -1;
		}
		node[min_x][min_y]->open = 2;
		Update(min_x, min_y);
	}

	return 0;
}

void AstarNode::Update(int x, int y)
{

	for (int i = x - 1; i < x + 2; i++)
	{
		if (i < 0)continue;
		else if (i == node.size())break;

		for (int j = y - 1; j < y + 2; j++)
		{
			if (j < 0)continue;
			else if (j == node[0].size()) break;
			if (i == x && j == y) continue;

			if (node[i][j]->open == 0 && !node[i][j]->start)
			{
				node[i][j]->open = 1;
				Cal(i, j, x, y);
				node[i][j]->parent = node[x][y];
			}

		}
	}


}

void AstarNode::Cal(int current_x, int current_y, int parent_x, int parent_y)
{
	int diag = 0;
	int hor = 0;
	if (abs(current_x - parent_x) > 0 && abs(current_y - parent_y) > 0) diag = 1;
	else hor = 1;

	int temp = node[parent_x][parent_y]->g_n + hor * 10 + diag * 14;
	if (node[current_x][current_y]->g_n == 0 || node[current_x][current_y]->g_n > temp)
	{
		if (node[current_x][current_y]->parent != NULL)
			node[current_x][current_y]->parent->open = -2;

		node[current_x][current_y]->g_n = temp;

	}

	int x = abs(current_x - end_x);
	int y = abs(current_y - end_y);

	diag = 0;
	hor = 0;

	while (x > 0 || y > 0)
	{
		if (x > 0 && y > 0)
		{
			x--;
			y--;
			diag++;
		}
		else if (x > 0)
		{
			x--;
			hor++;
		}
		else
		{
			y--;
			hor++;
		}
	}

	node[current_x][current_y]->h_n = hor * 10 + diag * 14;
	node[current_x][current_y]->f_n = node[current_x][current_y]->h_n + node[current_x][current_y]->g_n;
}

void AstarNode::FindWay()
{
	Node* current = node[end_x][end_y];
	while (current != NULL)
	{
		current->parent->child = current;
		
		current = current->parent;
		if (current->start == TRUE)
		{
			current = current->child;
			while (current->end == FALSE)
			{
				current->open = 3;
				current = current->child;
			}
			break;
		}
	}


}

int AstarNode::InRect(POINT ptMousePos, int startEndSelect)
{
	for (int i = 0; i < node.size(); i++)
	{
		for (int j = 0; j < node[i].size(); j++)
		{
			if (ptMousePos.x < 100 + j * 100 && ptMousePos.x > j * 100
				&& ptMousePos.y < 100 + i * 100 && ptMousePos.y > i * 100)
			{
				if (startEndSelect == 0)
				{
					start_x = i;
					start_y = j;
					node[start_x][start_y]->start = true;
				}
				else if (startEndSelect == 1)
				{
					end_x = i;
					end_y = j;
					node[end_x][end_y]->end = true;
				}
				return 1;
			}
		}
	}

	return 0;
}

void AstarNode::Reset()
{
	for (int i = 0; i < node.size(); i++)
	{
		for (int j = 0; j < node[i].size(); j++)
		{
			node[i][j]->open = 0;
			node[i][j]->parent = nullptr;
			node[i][j]->child = nullptr;
			node[i][j]->f_n = node[i][j]->g_n = node[i][j]->h_n = 0;
			node[i][j]->start = false;
			node[i][j]->end = false;
		}
	}

	for (auto e : block)
	{
		e->open = -1;
	}
}

RECT* AstarNode::Move(HDC hdc, int call)
{
	Node* current = node[start_x][start_y];
	int move_distance;
	int horizontal = 0, vertical = 0;
	RECT* rect;
	for (int i = 0; i < call; i++)
	{
		if (current->end==TRUE)
		{
			rect = new RECT{ -1, -1, -1, -1 };
			return rect;
		}
		move_distance = current->child->g_n - current->g_n;
		if (move_distance == 10)
		{
			if (current->child->point.x == current->point.x)
			{
				if (current->child->point.y > current->point.y)
					vertical++;
				else vertical--;
			}

			if (current->child->point.y == current->point.y)
			{
				if (current->child->point.x > current->point.x)
					horizontal++;
				else horizontal--;
			}
		}
		if (move_distance == 14)
		{
			if (current->child->point.y > current->point.y)
				vertical++;
			else vertical--;
			if (current->child->point.x > current->point.x)
				horizontal++;
			else horizontal--;
		}

		current = current->child;
	}


	rect = new RECT{ 25 + (start_y + vertical) * 100, 25 + (start_x + horizontal) * 100,
			75 + (start_y + vertical) * 100, 75 + (start_x + horizontal) * 100 };

	return rect;
}
