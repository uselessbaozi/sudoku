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
	int cursorRow;
	int cursorCol;

	//对单个格子进行深度优先搜索
	bool SetSingleGrid(int y, int x, int IsCreate = 1);

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
	s.ShowData();
	return 0;
}

bool Sukodu::SetSingleGrid(int row, int col, int IsCreate)
{
	//行位置列位置合法化
	if (col >= 9)
	{
		row++;
		col = 0;
	}
	if (row >= 9)
		row = 0;

	//若非创建时寻找下一个空格
	if (!IsCreate)
	{
		int flag(0);
		for (int i = row; i < 9; i++)
		{
			for (int j = col; j < 9; j++)
				if (data[i][j] == 0)
				{
					col = j;
					row = i;
					flag = 1;
					break;
				}
			if (flag)
				break;
		}
		if (!flag)
			return true;
	}

	//DFS
	int times(0);
	int start(rand() % 9);
	for (int i = start; times < 9; i++)
	{
		times++;
		if (i == 9)
			i = 0;
		if (JudgeCanSet(row, col, i + 1))		//判断目标数据是否合法
		{
			//cout << row << ' ' << col << ' ' << i + 1 << endl;
			data[row][col] = i + 1;
			if (col == 8 && row == 8)		//判断结尾
				return true;
			if (SetSingleGrid(row, col + 1, IsCreate))		//递归
				return true;
			data[row][col] = 0;
		}
	}
	return false;
}

Sukodu::Sukodu() :cursorRow(0), cursorCol(0)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			data[i][j] = 0;
}

void Sukodu::CreateSukodu()
{
	SetSingleGrid(0, 0);
}

bool Sukodu::JudgeCanSet(int row, int col, int num)
{
	//行判断
	for (int i = 0; i < 9; i++)
		if (data[row][i] == num)
			return false;

	//列判断
	for (int i = 0; i < 9; i++)
		if (data[i][col] == num)
			return false;

	//块判断
	int groupRow(row - (row % 3)), groupCol(col - (col % 3));
	for (int i = groupRow; i < groupRow + 3; i++)
		for (int j = groupCol; j < groupCol + 3; j++)
			if (data[i][j] == num)
				return false;

	return true;
}

void Sukodu::ShowData()
{
	//cmd指针移动至头部
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
