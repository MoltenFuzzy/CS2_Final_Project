#include <iostream>
#include <windows.h>   // WinApi header
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;   

void PrintBoard(string board[][7]);

void PutChip(string board[][7]);

int main()
{
	HANDLE  hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	// pick the colorattribute k you want

	// Color
	k = 12; // red = 12 
	k = 14; // yellow = 14

	SetConsoleTextAttribute(hConsole, k);

	// TODO change board size to const
	string board[6][7] =
	{
		{"[ ]","[ ]","[ ]","[ ]","[ ]","[ ]","[ ]"},
		{"[ ]","[ ]","[ ]","[ ]","[ ]","[ ]","[ ]"},
		{"[ ]","[ ]","[ ]","[ ]","[ ]","[ ]","[ ]"},
		{"[ ]","[ ]","[ ]","[ ]","[ ]","[ ]","[ ]"},
		{"[ ]","[ ]","[ ]","[ ]","[ ]","[ ]","[ ]"},
		{"[ ]","[ ]","[ ]","[ ]","[ ]","[ ]","[ ]"},
	};

	while (true /*!EndGame()*/) // TODO create bool function that defines when the game is over. Ex. Once 4 chips are connected
	{
		PrintBoard(board);

		PutChip(board);
	}

	return 0;
}

void PrintBoard(string board[][7])
{
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
	cout << endl;
}

// TODO May need another character for the chip for the bot. 

void PutChip(string board[][7]) // May be reused for the bot
{
	int column_pick; 
	cout << "Which column would you like? (1-7): ";
	cin >> column_pick;
	cout << endl;

	column_pick--; // index starts at 0

	for (int i = 6; i > 0; i--)
	{
		if (board[i][column_pick] == "[ ]")
		{
			board[i][column_pick] = "[O]";
			break;
		}
	}

}

bool EndGame(string board[][7])
{
	return true;
}

