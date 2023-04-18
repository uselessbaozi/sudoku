#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

class Sukodu
{
private:
	int data[9][9];
	int cursorX;
	int cursorY;
	bool SetSingleGrid(int x, int y);	
public:
	Sukodu();
	void CreateSukodu();
	bool JudgeCanSet(int x, int y, int num);
	void ShowData();
};

int main()
{
	srand(time(NULL));
	Sukodu s;
	s.CreateSukodu();
	s.ShowData();
	return 0;
}

bool Sukodu::SetSingleGrid(int x, int y)
{
	if (x >= 9)
	{
		y++;
		x = 0;
	}

	int times(0);
	int start(rand() % 9);
	for (int i = start; times < 9; i++)
	{
		times++;
		if (i == 9)
			i = 0;
		cout << x << ' ' << y << ' ' << i + 1 << endl;
		if (JudgeCanSet(x, y, i + 1))
		{
			data[x][y] = i + 1;
			//ShowData();
			//Sleep(500);
			if (x == 8 && y == 8)
				return true;
			else
				if (SetSingleGrid(x + 1, y))
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
	for (int i = 0; i < 9; i++)
		if (data[x][i] == num)
			return false;

	for (int i = 0; i < 9; i++)
		if (data[i][y] == num)
			return false;

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
