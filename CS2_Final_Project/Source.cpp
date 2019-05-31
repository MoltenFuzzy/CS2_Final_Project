/*
Name: Kent Phan
*/

#include <iostream>
#include <windows.h>   // WinApi header
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime> // Testing for AI, TODO delete later

using namespace std;   

// TODO add coin flip for who goes first
// TODO change the board to 2d char array

const int MAX_ROW = 6;
const int MAX_COL = 7;

void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole);

void StartGame(char board[MAX_ROW][MAX_COL], bool &player_won, HANDLE &hConsole);

void DeclareWinner(const HANDLE &hConsole, bool player_won);

bool EndGame(const char board[][MAX_COL], bool& player_win);

void BOT(char board[][MAX_COL]);

void PutChip(char board[][MAX_COL], char chip, bool player = true);

void BOTAI(char board[][MAX_COL], int &column_pick);

bool isColumnFull(const char board[][MAX_COL], int column_pick);

int Minimax(const char board[][MAX_COL]);

void clrscr();

void fillA(char a[MAX_ROW][MAX_COL], char ch);

bool RunAgain();

const int GREEN = 10; 
const int YELLOW = 14;
const int RED = 12;
const int BLUE = 9;
const int WHITE = 15;

// TODO Replace all instances of [O] & [0] with there respective constants

const char PLAYERCHIP = 'O';
const char BOTCHIP = '0';

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
		//clrscr(); // To clear the screen at the beginning of each game

		char board[MAX_ROW][MAX_COL] = {};

		fillA(board, ' ');

		bool player_won;

		// While it is not end of game, continue looping.
		// Note: EndGame returns true if it counts 4 chips in a row and !EndGame will change it to false, stopping the loop

		// TODO: add difficulty selection for AI

		StartGame(board, player_won, hConsole);

		//clrscr();

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
		cout << setw(17) << setfill(' ') << "You won!\n\n";
	else
		cout << setw(17) << setfill(' ') << "You lost!\n\n";
}

void StartGame(char board[MAX_ROW][MAX_COL], bool &player_won, HANDLE &hConsole)
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

		//clrscr(); // clears console screen

	}
}

void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole)
{
	SetConsoleTextAttribute(hConsole, RED);
	// Column indicators
	cout << " 1 " << " 2 " << " 3 " << " 4 " << " 5 " << " 6 " << " 7 \n";

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

	cout << endl;

	column_pick--; // index starts at 0

	for (int i = MAX_ROW - 1; i >= 0; i--)
	{
		if (board[i][column_pick] == ' ')
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
		column_pick = 1; // Create function that would return the column_pick using an algorithm

	} while(isColumnFull(board, column_pick));

	//cout << "Bot chooses column " << column_pick << endl;
}

void BOT(char board[][MAX_COL])
{
	PutChip(board, BOTCHIP, false);
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

	for (int row = MAX_ROW - 1; row >= 0; row--) // TODO used to be just 7 and not 7-1
	{
		for (int col = MAX_COL - 1; col >= 0; col--)
		{
			if (board[row][col] == PLAYERCHIP)
				row_Ochipcount++;

			else if (board[row][col] == BOTCHIP || board[row][col] == ' ')
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

			else if (board[row][col] == PLAYERCHIP || board[row][col] == ' ')
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

			else if (board[row][col] == BOTCHIP || board[row][col] == ' ')
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

			else if (board[row][col] == PLAYERCHIP || board[row][col] == ' ')
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

bool isColumnFull(const char board[][MAX_COL], int column_pick)
{
	int count = 0;
	
	column_pick--;

	for (int i = 0; i < 6; i++)
	{
		if (board[i][column_pick] != ' ')
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