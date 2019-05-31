/*
Name: Kent Phan
*/

#include <iostream>
#include <windows.h>   // WinApi header
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
#include "Connect4.h"

using namespace std;   

// TODO add coin flip for who goes first
// TODO change the board to 2d char array


int main()
{
	srand((unsigned)time(NULL)); // Delete later after BOTAI functionality is added

	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	// pick the colorattribute k you want

	// TODO change board size to const
	do
	{
		clrscr(); // To clear the screen at the beginning of each game

		char board[MAX_ROW][MAX_COL] = {};

		fillA(board, BLANKSPACE);

		bool player_won;

		// While it is not end of game, continue looping.
		// Note: EndGame returns true if it counts 4 chips in a row and !EndGame will change it to false, stopping the loop

		// TODO: add difficulty selection for AI, this will correspond to the depth/ how far the AI will look down the tree

		StartGame(board, player_won, hConsole);

		clrscr();

		DeclareWinner(hConsole, player_won);

		PrintBoard(board, hConsole);

		SetConsoleTextAttribute(hConsole, WHITE);

	} while (RunAgain());

	return 0;
}

void DeclareWinner(const HANDLE &hConsole, bool player_won)
{
	SetConsoleTextAttribute(hConsole, GREEN);
	if (player_won)
		cout << setw(17) << setfill(BLANKSPACE) << "You won!\n\n";
	else
		cout << setw(17) << setfill(BLANKSPACE) << "You lost!\n\n";
}

void StartGame(char board[MAX_ROW][MAX_COL], bool &player_won, HANDLE &hConsole)
{

	// rand range = 0 to 1; if % 2 + 1, then 1 to 2
	bool chance = rand() % 2; // Switching starting player

	if (chance)
	{
		while (!EndGame(board, player_won)) // TODO create bool function that defines when the game is over. Ex. Once 4 chips are connected
		{
			SetConsoleTextAttribute(hConsole, YELLOW);
			PrintBoard(board, hConsole);

			SetConsoleTextAttribute(hConsole, GREEN);
			PutChip(board, PLAYERCHIP);

			SetConsoleTextAttribute(hConsole, YELLOW);
			PrintBoard(board, hConsole);

			// Added bc if player connects 4 before the bot and then the bot connects 4, Player will lose even though they won first
			if (EndGame(board, player_won))
				break;

			// Bot that will play against player
			SetConsoleTextAttribute(hConsole, GREEN);
			BOT(board);

			clrscr(); // clears console screen

		}
	}
	else
	{
		while (!EndGame(board, player_won)) // TODO create bool function that defines when the game is over. Ex. Once 4 chips are connected
		{

			SetConsoleTextAttribute(hConsole, GREEN);
			BOT(board);

			SetConsoleTextAttribute(hConsole, YELLOW);
			PrintBoard(board, hConsole);

			// Added bc if player connects 4 before the bot and then the bot connects 4, Player will lose even though they won first
			if (EndGame(board, player_won))
				break;

			// Bot that will play against player
			SetConsoleTextAttribute(hConsole, GREEN);
			PutChip(board, PLAYERCHIP);

			clrscr(); // clears console screen

		}
	}
}

void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole)
{
	SetConsoleTextAttribute(hConsole, RED);
	// Column indicators
	cout << " 1  2  3  4  5  6  7 \n";

	SetConsoleTextAttribute(hConsole, BLUE);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j == 6)
			{
				if (board[i][j] == PLAYERCHIP)
				{
					cout << "[";
					SetConsoleTextAttribute(hConsole, RED);
					cout << board[i][j];
					SetConsoleTextAttribute(hConsole, BLUE);
					cout << "]\n";
				}
				else
				{
					cout << "[";
					SetConsoleTextAttribute(hConsole, YELLOW);
					cout << board[i][j];
					SetConsoleTextAttribute(hConsole, BLUE);
					cout << "]\n";
				}
			}
			else
			{
				if (board[i][j] == PLAYERCHIP)
				{
					cout << "[";
					SetConsoleTextAttribute(hConsole, RED);
					cout << board[i][j];
					SetConsoleTextAttribute(hConsole, BLUE);
					cout << "]";
				}
				else
				{
					cout << "[";
					SetConsoleTextAttribute(hConsole, YELLOW);
					cout << board[i][j];
					SetConsoleTextAttribute(hConsole, BLUE);
					cout << "]";
				}
			}
		}
	}
	cout << endl;
}

// TODO May need another character for the chip for the bot. 

void PutChip(char board[][MAX_COL], char chip, bool isPlayer) // May be reused for the bot
{
	int column_pick = 0;

	if (isPlayer)
	{
		cout << "Which column would you like? (1-7): ";
		cin >> column_pick;
		while (column_pick > 7 || column_pick < 1)
		{
			cout << "\nColumn does not exist!\n\n";
			cout << "Which column would you like? (1-7): ";
			cin >> column_pick;
		}
		while (isColumnFull(board, column_pick))
		{
			cout << "\nColumn is full!\n\n";
			cout << "Which column would you like? (1-7): ";
			cin >> column_pick;
		}
	}
	else
	{
		// Want to loop until the column picked is not full 
		BOTAI(board, column_pick);
	}

	//cout << endl;

	column_pick--; // index starts at 0

	for (int i = MAX_ROW - 1; i >= 0; i--)
	{
		if (board[i][column_pick] == BLANKSPACE)
		{
			board[i][column_pick] = chip;
			break;
		}
	}

}

void BOTAI(char board[][MAX_COL], int &column_pick)
{
	do
	{

		//column_pick = Minimax(board, 4, true, ); // Create function that would return the column_pick using an algorithm

		column_pick = BestCol(board);

	} while(isColumnFull(board, column_pick));

	//cout << "Bot chooses column " << column_pick << endl;
}

void BOT(char board[][MAX_COL])
{
	PutChip(board, BOTCHIP, false);
}

bool isTermNode(const char board[][MAX_COL], bool player_won)
{
	// returns a leaf node/terminal node
	return (EndGame(board, player_won) || EndGame(board, player_won) /* add if board is full */);
}

int BestCol(const char board[][MAX_COL])
{
	vector<int> scores_v(7);

	if (board[MAX_ROW - 1][3] == BLANKSPACE)
		return 4; 


	// Add score algorithm +2 +4 +1000 etc


	// Returns largest element's index
	// This works
	int max_index = 0;

	for (int i = 0; i < scores_v.size(); i++)
	{ 
		if (scores_v.at(i) > scores_v.at(max_index))
		{
			max_index = i;
		}
	}

	return max_index + 1; // Turns index into the column 0-6 to 1-7
}

int Minimax(char board[][MAX_COL], int depth, bool MaximizingPlayer, bool player_won)
{
	bool isTerm = isTermNode(board, player_won);

	if (depth == 0 || isTerm /* add if board is full */)
	{
		if (isTerm)
		{
			if (EndGame(board, player_won))
				return INFINITY;
			else if (EndGame(board, player_won))
				return -INFINITY;
			else
				return 0;
		}
		else
		{
			int column_pick = 0; 
			BOTAI(board, column_pick);
			return column_pick;
		}
		
		if (MaximizingPlayer)
		{
			int value = -INFINITY; 

			int i = 0;

		}

	}


	return 0;
}

// TODO return by referrence if the player wins or bot wins
// HACK BUG: registers win even if its not 4 in a row // (I think this has been fixed)
// TODO imporve the loop as running multiple loops is not efficient
bool EndGame(const char board[][MAX_COL], bool& player_win)
{
	int row_Ochipcount = 0;
	int row_0chipcount = 0;

	// Counts Horizontal Chips for each player
	// HACK make sure they are next to each other, not just there are 4 in the row/column

	// Why does this work for decremeting, but when incrementing it does not count the others [ ][ ][ ][O][O][O][O]

	for (int row = MAX_ROW - 1; row >= 0; row--) 
	{
		for (int col = MAX_COL - 1; col >= 0; col--)
		{
			if (board[row][col] == PLAYERCHIP)
				row_Ochipcount++;

			else if (board[row][col] == BOTCHIP || board[row][col] == BLANKSPACE)
			{
				if (row_Ochipcount >= 4)
				{
					player_win = true;
					return true; // Someone has won, return true
				}
				else 
					row_Ochipcount = 0;
			}

			if (board[row][col] == BOTCHIP)
				row_0chipcount++;

			else if (board[row][col] == PLAYERCHIP || board[row][col] == BLANKSPACE)
			{
				if (row_0chipcount >= 4)
				{
					player_win = false;
					return true; // Someone has won, return true
				}
				else
					row_0chipcount = 0;
			}
		}
	}

	// Counts Vertical Chips for each player

	for (int col = MAX_COL - 1; col >= 0; col--)
	{
		for (int row = MAX_ROW - 1; row >= 0; row--)
		{
			if (board[row][col] == PLAYERCHIP)
				row_Ochipcount++;

			else if (board[row][col] == BOTCHIP || board[row][col] == BLANKSPACE)
			{
				if (row_Ochipcount >= 4)
				{
					player_win = true;
					return true; // Someone has won, return true
				}
				else
					row_Ochipcount = 0;
			}

			if (board[row][col] == BOTCHIP)
				row_0chipcount++;

			else if (board[row][col] == PLAYERCHIP || board[row][col] == BLANKSPACE)
			{
				if (row_0chipcount >= 4)
				{
					player_win = false;
					return true; // Someone has won, return true
				}
				else
					row_0chipcount = 0;
			}
		}
	}

	// Counts Diagonal Chips for each player
	// From left side
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		for (int col = MAX_COL - 1; col >= 0; col--)
		{
			if (row > 2 && col >= 3)
			{
				if (board[row][col] == PLAYERCHIP)
					row_Ochipcount++;
				if (board[row - 1][col - 1] == PLAYERCHIP)
					row_Ochipcount++;
				if (board[row - 2][col - 2] == PLAYERCHIP)
					row_Ochipcount++;
				if (board[row - 3][col - 3] == PLAYERCHIP)
					row_Ochipcount++;
				if (row_Ochipcount >= 4)
				{
					player_win = true;
					cout << "Won diagonally " << row_Ochipcount << endl;
					return true; // Someone has won, return true
				}
				else
				{
					row_Ochipcount = 0;
				}

				if (board[row][col] == BOTCHIP)
					row_0chipcount++;
				if (board[row - 1][col - 1] == BOTCHIP)
					row_0chipcount++;
				if (board[row - 2][col - 2] == BOTCHIP)
					row_0chipcount++;
				if (board[row - 3][col - 3] == BOTCHIP)
					row_0chipcount++;
				if (row_0chipcount >= 4)
				{
					player_win = false;
					cout << "Lost diagonally " << row_0chipcount << endl;
					return true; // Someone has won, return true
				}
				else
				{
					row_0chipcount = 0;
				}
			}
		}
	}

	// From Right side
	// TODO: There is a bug in the diagonal count 
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			if (row > 2 && col <= 3)
			{
				// TODO: Could I clean this up?
				if (board[row][col] == PLAYERCHIP)
					row_Ochipcount++;
				if (board[row - 1][col + 1] == PLAYERCHIP)
					row_Ochipcount++;
				if (board[row - 2][col + 2] == PLAYERCHIP)
					row_Ochipcount++;
				if (board[row - 3][col + 3] == PLAYERCHIP)
					row_Ochipcount++;
				if (row_Ochipcount >= 4)
				{
					player_win = true;
					cout << "Won diagonally " << row_Ochipcount << endl;
					return true; // Someone has won, return true
				}
				else
				{
					row_Ochipcount = 0;
				}

				if (board[row][col] == BOTCHIP)
					row_0chipcount++;
				if (board[row - 1][col + 1] == BOTCHIP)
					row_0chipcount++;
				if (board[row - 2][col + 2] == BOTCHIP)
					row_0chipcount++;
				if (board[row - 3][col + 3] == BOTCHIP)
					row_0chipcount++;
				if (row_0chipcount >= 4)
				{
					player_win = false;
					cout << "Lost diagonally " << row_0chipcount << endl;
					return true; // Someone has won, return true
				}
				else
				{
					row_0chipcount = 0;
				}
			}
		}
	}

	return false;
}

bool isBoardFull(const char board[][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (board[i][j] == BLANKSPACE)
				return false;
		}
	}
	return true;
}

bool isColumnFull(const char board[][MAX_COL], int column_pick)
{
	int count = 0;
	
	column_pick--;

	for (int i = 0; i < 6; i++)
	{
		if (board[i][column_pick] != BLANKSPACE)
		{
			count++; 
		}
	}

	if (count >= 6) // if the count is 6(row) is greater it should return true and ask for another pick
		return true;
	else
		return false;
}

void fillA(char a[MAX_ROW][MAX_COL], char ch)
{
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			a[i][j] = ch;
}

bool RunAgain()
{
	cin.ignore();
	cout << "Would you like to play again?(Y/N): ";
	string ans; 
	getline(cin, ans);

	cout << endl;

	return (tolower(ans[0]) == 'y');
}

// Taken from http://www.cplusplus.com/forum/articles/10515/
void clrscr()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}