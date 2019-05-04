#include <iostream>
#include <windows.h>   // WinApi header
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime> // Testing for AI, TODO delete later

using namespace std;   

void PrintBoard(string board[][7]);

void BOT(string board[6][7]);

void PutChip(string board[][7], string chip, bool player = true);

bool isColumnFull(string board[][7], int column_pick);

const int GREEN = 10; 
const int YELLOW = 14;
const int RED = 12;

const string PLAYERCHIP = "[O]";
const string BOTCHIP = "[0]";

int main()
{
	srand((unsigned)time(NULL));

	HANDLE hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	// pick the colorattribute k you want

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
		SetConsoleTextAttribute(hConsole, YELLOW);
		PrintBoard(board);

		SetConsoleTextAttribute(hConsole, GREEN);
		PutChip(board, PLAYERCHIP);

		SetConsoleTextAttribute(hConsole, YELLOW);
		PrintBoard(board);

		// Bot that will play against player
		SetConsoleTextAttribute(hConsole, GREEN);
		BOT(board);
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

void PutChip(string board[][7], string chip, bool player) // May be reused for the bot
{
	int column_pick = rand() % 7 + 1;

	if (player)
	{
		cout << "Which column would you like? (1-7): ";
		cin >> column_pick;
		while (column_pick > 7 || column_pick < 1)
		{
			cout << "Column does not exist!\n";
			cout << "Which column would you like? (1-7): ";
			cin >> column_pick;
		}
		while (isColumnFull(board, column_pick))
		{
			cout << "Column is full!\n";
			cout << "Which column would you like? (1-7): ";
			cin >> column_pick;
		}
	}
	else
	{
		// Want to loop until the column picked is not full
		while (isColumnFull(board, column_pick))
		{
			column_pick = rand() % 7 + 1;
		}
		cout << "Bot chooses column " << column_pick << endl;
	}

	cout << endl;

	column_pick--; // index starts at 0

	for (int i = 5; i >= 0; i--)
	{
		if (board[i][column_pick] == "[ ]")
		{
			board[i][column_pick] = chip;
			break;
		}
	}

}

void BOT(string board[6][7])
{
	PutChip(board, BOTCHIP, false);
}

bool EndGame(string board[][7])
{
	//for(board[])
	return true;
}

bool isColumnFull(string board[][7], int column_pick)
{
	int count = 0;
	
	column_pick--;

	for (int i = 0; i < 6; i++)
	{
		if (board[i][column_pick] != "[ ]")
		{
			count++; 
		}
	}

	if (count >= 6) // if the count is 6(row) is greater it should return true and ask for another pick
		return true;
	else
		return false;
}

