#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

class Sukodu
{
private:
	int data[9][9];

	//游玩时指针位置
	int cursorX;
	int cursorY;

	//对单个格子进行深度优先搜索
	bool SetSingleGrid(int x, int y);

public:
	Sukodu();

	//数独创建入口
	void CreateSukodu();

	//判断该数字是否可以合法填入
	bool JudgeCanSet(int x, int y, int num);

	//输出
	void ShowData();
};

int main()
{
	//设置种子
	srand(time(NULL));

	//创建数独
	Sukodu s;
	s.CreateSukodu();
	//s.ShowData();
	return 0;
}

bool Sukodu::SetSingleGrid(int x, int y)
{
	//换行
	if (x >= 9)
	{
		y++;
		x = 0;
	}

	//DFS
	int times(0);
	int start(rand() % 9);
	for (int i = start; times < 9; i++)
	{
		times++;
		if (i == 9)
			i = 0;
		if (JudgeCanSet(x, y, i + 1))		//判断目标数据是否合法
		{
			data[x][y] = i + 1;
			if (x == 8 && y == 8)		//判断结尾
				return true;
			else
				if (SetSingleGrid(x + 1, y))		//递归
					return true;
			data[x][y] = 0;
		}
	}
	data[x][y] = 0;
	return false;
}

Sukodu::Sukodu() :cursorX(0), cursorY(0)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			data[i][j] = 0;
}

void Sukodu::CreateSukodu()
{
	SetSingleGrid(0, 0);
}

bool Sukodu::JudgeCanSet(int x, int y, int num)
{
	//行判断
	for (int i = 0; i < 9; i++)
		if (data[x][i] == num)
			return false;

	//列判断
	for (int i = 0; i < 9; i++)
		if (data[i][y] == num)
			return false;

	//块判断
	int groupX(x - (x % 3)), groupY(y - (y % 3));
	for (int i = groupY; i < groupY + 3; i++)
		for (int j = groupX; j < groupX + 3; j++)
			if (data[j][i] == num)
				return false;

	return true;
}

void Sukodu::ShowData()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, cursorPos);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			cout << data[i][j];
		cout << endl;
	}

}
