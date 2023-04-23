#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <stdlib.h>
#include "MatLab/SudokuSolution.h"
using namespace std;

class Sukodu
{
private:
	int mid[9][9];
	int question[9][9];
	int answer[9][9];
	int wall[9][9];
	int haveAnswer;

	//游玩时指针位置
	int cursorRow;
	int cursorCol;

	//matlab矩阵
	mwArray sudoku;

	//对单个格子进行深度优先搜索
	bool SetSingleGrid(int y, int x, int combo);

public:
	Sukodu();

	//数独创建入口
	void CreateSukodu();

	//判断该数字是否可以合法填入
	bool JudgeCanSet(int row, int col, int num);

	//输出
	void ShowData();

	//挖坑
	void SetBlank(int num);

	//设置问题与答案
	void SetQA(int num);

	//游玩
	void Play();

	//向sukodu添加数据并求解
	void AddSudolu();
};

int main()
{
	//初始化
	srand(time(NULL));
	if (!SudokuSolutionInitialize())
		return 0;

	//创建数独
	Sukodu s;
	s.CreateSukodu();
	s.SetQA(20);

	//游玩
	s.ShowData();
	s.Play();

	return 0;
}

bool Sukodu::SetSingleGrid(int row, int col, int combo)
{
	//行位置列位置合法化
	if (col >= 9)
	{
		row++;
		col = 0;
	}
	if (row >= 9)
		row = 0;

	////若非创建时寻找下一个空格
	//if (!IsCreate)
	//{
	//	int flag(0);
	//	for (int i = row; i < 9; i++)
	//	{
	//		for (int j = col; j < 9; j++)
	//			if (question[i][j] == 0)
	//			{
	//				col = j;
	//				row = i;
	//				flag = 1;
	//				break;
	//			}
	//		if (flag)
	//			break;
	//	}
	//	if (!flag)
	//		return true;
	//}

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
			combo++;
			//cout << row << ' ' << col << ' ' << i + 1 << endl;
			question[row][col] = i + 1;
			if (combo==17)		//判断结尾
				return true;
			if (SetSingleGrid(row, col + 1, combo))		//递归
				return true;
			question[row][col] = 0;
			combo--;
		}
	}
	return false;
}

Sukodu::Sukodu() :cursorRow(0), cursorCol(0), sudoku(9, 9, mxDOUBLE_CLASS), haveAnswer(1), mid{}
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			answer[i][j] = question[i][j] = 0;
			wall[i][j] = 1;
		}
}

void Sukodu::CreateSukodu()
{
	do
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				question[i][j] = 0;
		question[0][0] = 1;
		question[1][3] = 2;
		question[2][6] = 3;
		question[3][1] = 4;
		question[4][4] = 5;
		question[5][7] = 6;
		question[6][2] = 7;
		question[7][5] = 8;
		question[8][8] = 9;

		/*int x(rand() % 9 + 1);
		while (x == question[0][0] || x == question[6][2] || x == question[8][8])
		{
			x++;
			if (x > 8)
				x = 1;
		}*/

		/*SetSingleGrid(0, 0, 0);*/


		AddSudolu();
	} while (!haveAnswer);
}

bool Sukodu::JudgeCanSet(int row, int col, int num)
{
	//行判断
	for (int i = 0; i < 9; i++)
		if (question[row][i] == num && i != col)
			return false;

	//列判断
	for (int i = 0; i < 9; i++)
		if (question[i][col] == num && i != row)
			return false;

	//块判断
	int groupRow(row - (row % 3)), groupCol(col - (col % 3));
	for (int i = groupRow; i < groupRow + 3; i++)
		for (int j = groupCol; j < groupCol + 3; j++)
			if (question[i][j] == num && i != row && j != col)
				return false;

	return true;
}

void Sukodu::ShowData()
{
	//cmd指针移动至头部
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0,0 });
	SetConsoleTextAttribute(hConsole, 0x07);
	cout << " ----- ----- ----- ----- ----- ----- ----- ----- ----- " << endl;
	for (int nowRow = 0; nowRow < 9; nowRow++)
	{
		cout << "|     |     |     |     |     |     |     |     |     |" << endl;
		cout << '|';
		for (int nowCol = 0; nowCol < 9; nowCol++)
		{
			cout << ' ';
			if (nowCol == cursorCol && nowRow == cursorRow)
			{
				SetConsoleTextAttribute(hConsole, 0x70);
				cout << ' ' << question[nowRow][nowCol] << ' ';
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			else
				cout << ' ' << question[nowRow][nowCol] << ' ';
			cout << " |";
		}
		cout << endl;
		cout << "|     |     |     |     |     |     |     |     |     |" << endl;
		cout << " ----- ----- ----- ----- ----- ----- ----- ----- ----- " << endl;
	}
}

void Sukodu::SetBlank(int num)
{
	int x(0), y(0);
	for (int i = 0; i < num; i++)
	{
		x = rand() % 9;
		y = rand() % 9;
		question[x][y] = 0;
		wall[x][y] = 0;
	}
}

void Sukodu::SetQA(int num)
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			question[i][j] = answer[i][j];
	SetBlank(num);
	ShowData();
}

void Sukodu::Play()
{
	int isExit(0);
	char key(0);
	while (!isExit)
	{
		key = _getch();
		switch (key)
		{
		case 'a':
			if (cursorCol > 0)
				cursorCol--;
			break;
		case 'c':
			if (wall[cursorRow][cursorCol] != 1)
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
			break;
		}
		if (key >= '1' && key <= '9' && wall[cursorRow][cursorCol] == 0)
		{
			question[cursorRow][cursorCol] = key - '0';
			if (key - '0' != answer[cursorRow][cursorCol])
			{
				AddSudolu();
			}
		}
		thread tsd(&Sukodu::ShowData, this);
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (question[i][j] != answer[i][j])
					continue;
		isExit = 0;
		tsd.join();
	}
	cout << "\nfinish";
}


void Sukodu::AddSudolu()
{
	//传入
	sudoku.SetData((int*)question, 81);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			mid[i][j] = (sudoku.Get(2, j + 1, i + 1));

	//分析
	try
	{
		SudokuSolution(1, sudoku, sudoku);
	}
	catch (mwException)
	{
		return;
	}

	//输出
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			mid[i][j] = (sudoku.Get(2, j + 1, i + 1));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (!JudgeCanSet(i, j, mid[i][j]))
			{
				haveAnswer = 0;
				return;
			}
	haveAnswer = 1;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			answer[i][j] = mid[i][j];
}
