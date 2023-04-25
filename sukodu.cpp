#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <thread>
using namespace std;

class Sukodu
{
private:
	int answer[9][9];
	int question[9][9];
	int mid[9][9];
	int state[9][9];
	int haveAns;

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

	//挖坑
	void SetBlank(int num);

	//设置问题与答案
	void SetQA(int num);

	//游玩
	void Play();

	//更新答案
	void UpdateAnswer();
};

//设置窗口大小
void SetWindowsSize(int height, int width);

int main()
{
	//初始化
	srand(time(NULL));
	SetWindowsSize(45, 60);
	
	//创建数独
	Sukodu s;
	s.CreateSukodu();
	s.SetQA(82);

	s.Play();
	return 0;
}

bool Sukodu::SetSingleGrid(int row, int col, int IsCreate)
{
	//若非创建时寻找下一个空格
	if (!IsCreate)
	{
		int flag(0);
		for (int i = col + 1; i < 9; i++)
			if (mid[row][i] == 0)
			{
				col = i;
				flag = 1;
				break;
			}
		if (!flag)
		{
			for (int i = row + 1; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
					if (mid[i][j] == 0)
					{
						col = j;
						row = i;
						flag = 1;
						break;
					}
				if (flag)
					break;
			}
		}
		if (!flag)
			return true;
	}
	else
	{
		col++;
		if (col >= 9)
		{
			row++;
			col = 0;
		}
		if (row >= 9)
			row = 0;
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
			//std::cout << row << ' ' << col << ' ' << i + 1 << endl;
			mid[row][col] = i + 1;
			if (col == 8 && row == 8)		//判断结尾
				return true;
			if (SetSingleGrid(row, col, IsCreate))		//递归
				return true;
			mid[row][col] = 0;
		}
	}
	return false;
}

Sukodu::Sukodu() :cursorRow(0), cursorCol(0), answer{ 0 }, question{ 0 }, mid{ 0 }, state { 0 }, haveAns(1) {}

void Sukodu::CreateSukodu()
{
	SetSingleGrid(0, -1);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			answer[i][j] = mid[i][j];
}

bool Sukodu::JudgeCanSet(int row, int col, int num)
{
	//行判断
	for (int i = 0; i < 9; i++)
		if (mid[row][i] == num && i != col)
			return false;

	//列判断
	for (int i = 0; i < 9; i++)
		if (mid[i][col] == num && i != row)
			return false;

	//块判断
	int groupRow(row - (row % 3)), groupCol(col - (col % 3));
	for (int i = groupRow; i < groupRow + 3; i++)
		for (int j = groupCol; j < groupCol + 3; j++)
			if (mid[i][j] == num && i != row && j != col)
				return false;

	return true;
}

void Sukodu::ShowData()
{
	//cmd指针移动至头部
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0,0 });

	SetConsoleTextAttribute(hConsole, 0x07);
	std::cout << " ----- ----- ----- ----- ----- ----- ----- ----- ----- " << endl;
	for (int nowRow = 0; nowRow < 9; nowRow++)
	{
		std::cout << "|     |     |     |     |     |     |     |     |     |" << endl;
		std::cout << '|';
		for (int nowCol = 0; nowCol < 9; nowCol++)
		{
			std::cout << ' ';
			if (nowCol == cursorCol && nowRow == cursorRow)
			{
				if (state[nowRow][nowCol] == 1)
					SetConsoleTextAttribute(hConsole, 0x76);
				else
					SetConsoleTextAttribute(hConsole, 0x70);
				std::cout << ' ' << question[nowRow][nowCol] << ' ';
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			else if (state[nowRow][nowCol] == 1)
			{
				SetConsoleTextAttribute(hConsole, 0x06);
				std::cout << ' ' << question[nowRow][nowCol] << ' ';
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			else
				std::cout << ' ' << question[nowRow][nowCol] << ' ';
			std::cout << " |";
		}
		std::cout << endl;
		std::cout << "|     |     |     |     |     |     |     |     |     |" << endl;
		std::cout << " ----- ----- ----- ----- ----- ----- ----- ----- ----- " << endl;
	}
}

void Sukodu::SetBlank(int num)
{
	int x(0), y(0);
	for (int i = 0; i < num && i < 81; i++)
	{
		x = rand() % 9;
		y = rand() % 9;
		while (question[x][y] == 0)
		{
			y++;
			if (y >= 9)
			{
				x++;
				y = 0;
			}
			if (x >= 9)
				x = 0;
		}
		question[x][y] = 0;
		state[x][y] = 0;
	}
}

void Sukodu::SetQA(int num)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			question[i][j] = answer[i][j];
			state[i][j] = 1;
		}
	SetBlank(num);
	ShowData();
}

void Sukodu::Play()
{
	int isExit(0), flag(0);
	char key(0);
	while (!isExit)
	{
		flag = 0;
		key = _getch();
		switch (key)
		{
		case 'a':
			if (cursorCol > 0)
				cursorCol--;
			break;
		case 'c':
			if (state[cursorRow][cursorCol] != 1)
				question[cursorRow][cursorCol] = 0;
			break;
		case 'd':
			if (cursorCol < 8)
				cursorCol++;
			break;
		case 's':
			if (cursorRow < 8)
				cursorRow++;
			break;
		case 'w':
			if (cursorRow > 0)
				cursorRow--;
			break;
		default:
			flag = 1;
			break;
		}
		if (key >= '1' && key <= '9' && state[cursorRow][cursorCol] == 0)
		{
			flag = 0;
			question[cursorRow][cursorCol] = key - '0';
			if (key - '0' != answer[cursorRow][cursorCol])
			{
				UpdateAnswer();
			}
		}
		if (flag)
			continue;
		else
			flag = 0;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
				if (question[i][j] != answer[i][j])
				{
					flag = 1;
					break;
				}
			if (flag)
				break;
		}
		ShowData();
		if (flag)
			continue;
		isExit = 1;
	}
	std::cout << "\nfinish";
}

void Sukodu::UpdateAnswer()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			mid[i][j] = question[i][j];
	if (!JudgeCanSet(cursorRow, cursorCol, mid[cursorRow][cursorCol]))
	{
		haveAns = 0;
		return;
	}
	if (!SetSingleGrid(0, -1, 0))
		haveAns = 0;
	else
	{
		haveAns = 1;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				answer[i][j] = mid[i][j];
	}
}

void SetWindowsSize(int height, int width)
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hStdOutput, TRUE, &wrt); // 设置窗体尺寸
	COORD coord = { width, height };
	SetConsoleScreenBufferSize(hStdOutput, coord); // 设置缓冲尺寸
}
