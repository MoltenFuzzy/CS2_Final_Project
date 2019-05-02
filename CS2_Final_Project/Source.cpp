// color your text in Windows console mode
// colors are 0=black 1=blue 2=green and so on to 15=white  
// colorattribute = foreground + background * 16
// to get red text on yellow use 4 + 14*16 = 228
// light red on yellow would be 12 + 14*16 = 236
// a Dev-C++ tested console application by  vegaseat  07nov2004
#include <iostream>
#include <windows.h>   // WinApi header
#include <iomanip>
#include <cstdlib>

using namespace std;    // std::cout, std::cin

int main()
{
	HANDLE  hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	// pick the colorattribute k you want

	k = 12; // red = 12 
	k = 14; // yellow = 14

	SetConsoleTextAttribute(hConsole, k);

	char board[6][7] =
	{
		{'o','o','o','o','o','o','o'},
		{'o','o','o','o','o','o','o'},
		{'o','o','o','o','o','o','o'},
		{'o','o','o','o','o','o','o'},
		{'o','o','o','o','o','o','o'},
		{'o','o','o','o','o','o','o'}
	};

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j == 6)
				cout << board[i][j] << endl;
			else
				cout << board[i][j] << " ";
		}
	}

	return 0;
}

