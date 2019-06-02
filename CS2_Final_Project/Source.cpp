/*
Name: Kent Phan
*/

#include <iostream>
#include <windows.h> 
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
#include "Connect4.h"

using namespace std;   

int main()
{
	srand((unsigned)time(NULL)); // Delete later after BOTAI functionality is added

	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	// pick the colorattribute k you want

	do
	{
		clrscr(); // To clear the screen at the beginning of each game

		char board[MAX_ROW][MAX_COL] = {};

		fillA(board, EMPTY);

		// While it is not end of game, continue looping.
		// Note: EndGame returns true if it counts 4 chips in a row and !EndGame will change it to false, stopping the loop

		// TODO: add difficulty selection for AI, this will correspond to the depth/ how far the AI will look down the tree

		StartGame(board, hConsole);

		clrscr();

		DeclareWinner(board, hConsole);

		PrintBoard(board, hConsole);

		SetConsoleTextAttribute(hConsole, WHITE);

	} while (RunAgain());

	return 0;
}

void DeclareWinner(const char board[][MAX_COL], HANDLE &hConsole)
{
	SetConsoleTextAttribute(hConsole, GREEN);
	if (EndGame(board, PLAYERCHIP))
		cout << setw(17) << setfill(EMPTY) << "You won!\n\n";
	else if (EndGame(board, BOTCHIP))
		cout << setw(17) << setfill(EMPTY) << "You lost!\n\n";
}

void StartGame(char board[][MAX_COL], HANDLE &hConsole)
{
	// rand range = 0 to 1; if % 2 + 1, then 1 to 2
	bool chance = rand() % 2; // Switching starting player

	if (chance)
	{
		while (!(EndGame(board, PLAYERCHIP) || EndGame(board, BOTCHIP))) 
		{
			SetConsoleTextAttribute(hConsole, YELLOW);
			PrintBoard(board, hConsole);

			SetConsoleTextAttribute(hConsole, GREEN);
			PutChip(board, PLAYERCHIP);

			SetConsoleTextAttribute(hConsole, YELLOW);
			PrintBoard(board, hConsole);

			// Added bc if player connects 4 before the bot and then the bot connects 4, Player will lose even though they won first
			if (EndGame(board, PLAYERCHIP) || EndGame(board, BOTCHIP))
				break;

			// Bot that will play against player
			SetConsoleTextAttribute(hConsole, GREEN);
			BOT(board);

			clrscr(); // clears console screen

		}
	}
	else
	{
		while (!(EndGame(board, PLAYERCHIP) || EndGame(board, BOTCHIP))) 
		{

			SetConsoleTextAttribute(hConsole, GREEN);

			BOT(board);

			SetConsoleTextAttribute(hConsole, YELLOW);
			PrintBoard(board, hConsole);

			// Added bc if player connects 4 before the bot and then the bot connects 4, Player will lose even though they won first
			if (EndGame(board, PLAYERCHIP) || EndGame(board, BOTCHIP))
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
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
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

void PutChip(char board[][MAX_COL], char chip)
{
	int column_pick = 0;

	if (chip == PLAYERCHIP)
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
		column_pick--;
	}
	else
	{
		// Want to loop until the column picked is not full 
		do
		{
			// pick best column will already return a valid column(1-7)
			column_pick = PickBestCol(board, BOTCHIP);
		} while (isColumnFull(board, column_pick));
		//column_pick = rand() % 7 + 1;
	}

	//cout << endl;

	//column_pick--; // index starts at 0

	DropChip(board, column_pick, chip);

}

void BOT(char board[][MAX_COL])
{
	PutChip(board, BOTCHIP);
}

bool isTermNode(const char board[][MAX_COL], bool player_won)
{
	// returns a leaf node/terminal node
	return (EndGame(board, player_won) || EndGame(board, player_won) /* add if board is full */);
}

vector<int> GetValidCols(const char board[][MAX_COL])
{
	vector<int> valid_cols;
	for (int col = 0; col < MAX_COL; col++)
	{
		if (IsValidXY(board, col))
		{
			valid_cols.push_back(col);
		}
	}
	return valid_cols;
}

// TODO: Fix issue with column filling up. Specifically column 2. 
int score_col(const char board[][MAX_COL], char chip)
{
	// Horizontal scoring
	int score = 0;
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		vector<char> row_v;
		for (int col = 0; col < MAX_COL; col++) 
		{
			row_v.push_back(board[row][col]);
			// Subtracting the max amount of cols and the amount of connected chips/pieces to get 3 which keeps it from going out of bounds
		}

		vector<char> window; 
		for (int i = 0; i < row_v.size() - 3; i++)
		{
			for (int j = i; j < i + 4; j++)
			{
				window.push_back(row_v.at(j));
			}

			score += ScoreTheBoard(window, chip);

			window.clear();
			window.resize(0);
		}

		row_v.clear();
		row_v.resize(0);
	}

	// Vertical scoring
	for (int col = 0; col < MAX_COL; col++)
	{
		vector<char> col_v;
		for (int row = MAX_ROW - 1; row >= 0; row--)
		{
			col_v.push_back(board[row][col]);
			// Subtracting the max amount of cols and the amount of connected chips/pieces to get 3 which keeps it from going out of bounds
		}

		vector<char> window;
		for (int i = 0; i < col_v.size() - 3; i++)
		{
			for (int j = i; j < i + 4; j++)
			{
				window.push_back(col_v.at(j));
			}

			score += ScoreTheBoard(window, chip);

			window.clear();
			window.resize(0);
		}

		col_v.clear();
		col_v.resize(0);
	}

	return score;
}

int ScoreTheBoard(vector<char> window, char chip)
{
	char opp_chip = PLAYERCHIP;

	if (chip == PLAYERCHIP)
		opp_chip = BOTCHIP;

	int count_chip = CountChar(window, chip);
	int count_opp_chip = CountChar(window, opp_chip);
	int count_empty = CountChar(window, EMPTY);

	int score = 0;

	if (count_chip == 4)
		score += 100;
	else if (count_chip == 3 && count_empty == 1)
		score += 5;
	else if (count_chip == 2 && count_empty == 2)
		score += 2;

	if (count_opp_chip == 3 && count_empty == 1)
		score -= 4;

	return score;
}

int PickBestCol(char board[][MAX_COL], char chip)
{
	vector<int> valid_cols = GetValidCols(board);

	int best_score = 0;
	int best_col = 3;

	for (int col = 1; col <= valid_cols.size(); col++)
	{
		char temp_board[MAX_ROW][MAX_COL] = {};
		fillA(temp_board, EMPTY);
		CopyArray(board, temp_board, MAX_ROW, MAX_COL);
		DropChip(temp_board, col, chip);
		int score = score_col(temp_board, chip);
		if (score > best_score)
		{
			best_score = score; 
			best_col = col;
		}
	}

	return best_col;
}

void DropChip(char board[][MAX_COL], int col, char chip)
{
	for (int i = MAX_ROW - 1; i >= 0; i--)
	{
		if (board[i][col] == EMPTY)
		{
			board[i][col] = chip;
			break;
		}
	}
}


// TODO: Fix bug that sometimes counts the pieces incorrectly
bool EndGame(const char board[][MAX_COL], char piece)
{
	char opp_piece; 

	if (piece == PLAYERCHIP)
		opp_piece = BOTCHIP;
	else
		opp_piece = PLAYERCHIP;

	int piece_count = 0;

	const int WINCOUNT = 4;

	// Counts Horizontal Chips for each player

	for (int row = MAX_ROW - 1; row >= 0; row--) 
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			if (board[row][col] == piece)
				piece_count++;

			if (piece_count >= WINCOUNT)
			{
				cout << "  Horizontal Win for ";
				if (piece == PLAYERCHIP)
					cout << "Player" << endl;
				else
					cout << "BOT" << endl;
				return true; // Someone has won, return true
			}
			else if (board[row][col] == opp_piece || board[row][col] == EMPTY)
				piece_count = 0;
		}
		piece_count = 0;
	}

	// Counts Vertical Chips for each player

	for (int col = 0; col < MAX_COL; col++)
	{
		for (int row = MAX_ROW - 1; row >= 0; row--)
		{
			if (board[row][col] == piece)
				piece_count++;

			if (piece_count >= WINCOUNT)
			{
				cout << "  Vertical Win for ";
				if (piece == PLAYERCHIP)
					cout << "Player" << endl;
				else
					cout << "BOT" << endl;
				return true; // Someone has won, return true
			}
			else if (board[row][col] == opp_piece || board[row][col] == EMPTY)
				piece_count = 0;
			
		}
		piece_count = 0;
	}

	const int MAX_BOUND = 4; 
	const int ROW_BOUND = 2; 
	const int COL_BOUND = 3;
	// Counts Diagonal Chips for each player
	// From left side
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		for (int col = MAX_COL - 1; col >= 0; col--)
		{
			// Cannot be less than ROWBOUND(2) & COLBOUND(3) BC when it is passed those, a connect 4 in a row is no longer possible
			if (row > ROW_BOUND && col >= COL_BOUND)
			{
				for (int i = 0; i < MAX_BOUND; i++)
					if (board[row - i][col - i] == PLAYERCHIP)
						piece_count++;
			
				if (piece_count >= WINCOUNT)
				{
					//player_win = true;
					cout << "  Diagonal Win "; 
					if (piece == PLAYERCHIP)
						cout << "Player" << endl;
					else
						cout << "BOT" << endl;
					return true; // Someone has won, return true
				}
				piece_count = 0;
				
			}
		}
		piece_count = 0;
	}

	// From Right side
	// TODO: There is a bug in the diagonal count 
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			// Cannot be less than ROWBOUND(2) & COLBOUND(3) BC when it is passed those, a connect 4 in a row is no longer possible
			if (row > ROW_BOUND && col <= COL_BOUND)
			{
				for (int i = 0; i < MAX_BOUND; i++)
					if (board[row - i][col + i] == piece)
						piece_count++;

				if (piece_count >= WINCOUNT)
				{
					//player_win = true;
					cout << "  Diagonal Win " << piece << endl;
					if (piece == PLAYERCHIP)
						cout << "Player" << endl;
					else
						cout << "BOT" << endl;
					return true; // Someone has won, return true
				}
				piece_count = 0;
			}
		}
		piece_count = 0;
	}

	return false;
}

bool isBoardFull(const char board[][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (board[i][j] == EMPTY)
				return false;
		}
	}
	return true;
}

bool isColumnFull(const char board[][MAX_COL], int column_pick)
{
	int count = 0;
	
	column_pick--;

	for (int i = 0; i < MAX_ROW; i++)
	{
		if (board[i][column_pick] != EMPTY)
		{
			count++; 
		}
	}

	if (count >= MAX_ROW) // if the count is 6(row) is greater it should return true and ask for another pick
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

bool IsValidXY(const char board[][MAX_COL], int col)
{
	return board[MAX_ROW - 1][col] == EMPTY;
}

int get_next_open_row(const char board[][MAX_COL], int col)
{
	for (int row = 0; row < MAX_ROW; row++)
		if (board[row][col] == EMPTY)
			return row;
}

void CopyArray(const char a1[][MAX_COL], char a2[][MAX_COL], int row_size, int col_size)
{
	for (int i = 0; i < row_size; i++)
		for(int j = 0; j < col_size; j++)
			a2[i][j] = a1[i][j];
}

int CountChar(vector<char> v, char chip)
{
	// Assuming this is used by the AI
	char opp_chip = PLAYERCHIP;

	if (chip == PLAYERCHIP)
		opp_chip = BOTCHIP;

	int count = 0;

	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i) == chip)
			count++;
		else if (v.at(i) == opp_chip)
			count = 0;
	}

	return count;
}