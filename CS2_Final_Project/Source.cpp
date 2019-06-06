//Final Project
//Author: Kent Phan
//Email Address: kphan9@go.pasadena.edu
//Description: Connect 4 With AI
//Last Changed: 6/2/2019

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

		char board[MAX_ROW][MAX_COL] = {};
		// for testing connect 4 in a rows
		//{
		//	{' ','0',' ',' ',' ',' ',' '},
		//	{' ',' ','0',' ',' ',' ',' '},
		//	{' ',' ',' ','0',' ',' ',' '},
		//	{' ',' ',' ',' ','0',' ',' '},
		//	{' ',' ',' ',' ',' ',' ',' '},
		//	{' ',' ',' ',' ',' ',' ',' '},
		//};

		fillA(board, EMPTY);

		/*if (EndGame(board, BOTCHIP))
			cout << "Win!\n";*/

		// While it is not end of game, continue looping.
		// Note: EndGame returns true if it counts 4 chips in a row and !EndGame will change it to false, stopping the loop

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
	else if (isBoardFull(board))
		cout << setw(17) << setfill(EMPTY) << "You tied!\n\n";
}

void StartGame(char board[][MAX_COL], HANDLE &hConsole)
{

	clrscr(); // If player runs again it will clear the screen at the beginning always

	// rand range = 0 to 1; if % 2 + 1, then 1 to 2
	bool chance = rand() % 2; // Switching starting player

	// EndGame includes a if the board is full and no one has won
	while (!(EndGame(board, PLAYERCHIP) || EndGame(board, BOTCHIP)))
	{

		if (chance) // Player goes 1st
		{
			PrintBoard(board, hConsole);
			SetConsoleTextAttribute(hConsole, GREEN);
			GameInput(board, PLAYERCHIP);
			clrscr();
			PrintBoard(board, hConsole);
			clrscr();
		}
		else  // Bot goes 1st
		{
			PrintBoard(board, hConsole);
			Sleep(300);
			BOT(board);
			clrscr();
			PrintBoard(board, hConsole);
			clrscr();
		}

		// Added bc if player connects 4 before the bot and then the bot connects 4, Player will lose even though they won first
		if (EndGame(board, PLAYERCHIP) || EndGame(board, BOTCHIP) ) // TODO: ADD A TIE 
			break;
		
		if (chance) // Bot goes 2nd
		{
			PrintBoard(board, hConsole);
			Sleep(300);
			BOT(board);
			clrscr();
			PrintBoard(board, hConsole);
			clrscr();
		}
		else // Player goes 2nd
		{
			PrintBoard(board, hConsole);
			SetConsoleTextAttribute(hConsole, GREEN);
			GameInput(board, PLAYERCHIP);
			clrscr();
			PrintBoard(board, hConsole);
			clrscr();
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

void GameInput(char board[][MAX_COL], char chip)
{
	int column_pick = 0;

	if (chip == PLAYERCHIP)
	{
		cout << "Which column would you like? (1-7): ";
		cin >> column_pick;
		cin.clear();
		cin.ignore();

		while (column_pick > 7 || column_pick < 1)
		{
			cout << "\nColumn does not exist!\n\n";
			cout << "Which column would you like? (1-7): ";
			cin >> column_pick;
			cin.clear();
			cin.ignore();
		}
		while (isColumnFull(board, column_pick))
		{
			cout << "\nColumn is full!\n\n";
			cout << "Which column would you like? (1-7): ";
			cin >> column_pick;
			cin.clear();
			cin.ignore();
		}
	}
	else
	{
		// Want to loop until the column picked is not full 
		do
		{
			// pick best column will already return a valid column(1-7)
			column_pick = PickBestCol(board, chip);

		} while (isColumnFull(board, column_pick));
		//column_pick = rand() % 7 + 1;
	}

	//cout << endl;

	DropChip(board, column_pick, chip);

}

void BOT(char board[][MAX_COL])
{
	GameInput(board, BOTCHIP);
}

int score_col(const char board[][MAX_COL], char chip)
{
	const int WINDOW_SIZE = 4; // [0 0 0 0] checks if it is a connect 4 by sorting the chip sequences into windows and evaluating them.
	const int ROW_BOUND = 3; 

	int score = 0;

	// Horizontal scoring

	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		vector<char> row_v;
		for (int col = 0; col < MAX_COL; col++)
		{
			row_v.push_back(board[row][col]);
			// Subtracting the max amount of cols and the amount of connected chips/pieces to get 3 which keeps it from going out of bounds
		}

		for (int i = 0; i < row_v.size() - 3; i++)
		{
			vector<char> window;
			for (int j = i; j < i + WINDOW_SIZE; j++)
			{
				window.push_back(row_v.at(j));
			}
			score += ScoreWindow(window, chip);
		}
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

		for (int i = 0; i < col_v.size() - 3; i++)
		{
			vector<char> window;
			for (int j = i; j < i + WINDOW_SIZE; j++)
			{
				window.push_back(col_v.at(j));
			}

			score += ScoreWindow(window, chip);
		}
	}

	// Diagonal from Left Scoring(\)
	for (int row = (MAX_ROW - 1) - ROW_BOUND; row >= 0; row--)
	{
		for (int col = 0; col <= MAX_COL - 3; col++)
		{
			vector<char> window;
			for (int i = 0; i < WINDOW_SIZE; i++)
			{
				window.push_back(board[row + i][col + i]);
			}
			score += ScoreWindow(window, chip);
		}
	}
	
	// Diagonal from Right Scoring(/)
	for (int row = (MAX_ROW - 1) - ROW_BOUND; row >= 0; row--)
	{
		for (int col = 0; col <= MAX_COL - 3; col++)
		{
			vector<char> window;
			for (int i = 0; i < WINDOW_SIZE; i++)
			{
				// TODO: remove 3 and replace it with the window bound
				// Adding a row bound(3) bc it is str
				window.push_back(board[row - i + ROW_BOUND][col + i]);
			}
			score += ScoreWindow(window, chip);
		}
	}

	const int CENTER_COL = 3;

	// Preference Center
	vector<char> center_v;

	// Stores the enter center column into a vector
	for (int i = MAX_ROW - 1; i >= 0; i--)
		center_v.push_back(board[i][CENTER_COL]);

	// Counts the amount of chips that are in the center based on the player's turn
	int count_center = CountChar(center_v, chip);

	// Multiplies how many chips are in the center column to make the AI favor the center as it is most advantagous
	score += count_center * 6; 

	return score;
}

int ScoreWindow(vector<char> window, char chip)
{
	// Can change these values to better the return
	const int MUST_PUT = 200;
	const int SHOULD_PUT = 10;
	const int OKAY_PUT = 5;
	const int PREVENT_LOSS = 100;

	char opp_chip = PLAYERCHIP;

	if (chip == PLAYERCHIP)
		opp_chip = BOTCHIP;

	int count_chip = CountChar(window, chip);
	int count_opp_chip = CountChar(window, opp_chip);
	int count_empty = CountChar(window, EMPTY);

	int score = 0;

	if (count_chip == WIN_CONNECT)
		score += MUST_PUT;
	else if (count_chip == 3 && count_empty == 1)
		score += SHOULD_PUT;
	else if (count_chip == 2 && count_empty == 2)
		score += OKAY_PUT;

	if (count_opp_chip == 3 && count_empty == 1)
		score -= PREVENT_LOSS;

	return score;
}

int PickBestCol(char board[][MAX_COL], char chip)
{
	// large negative number so that it will be able to block the opponent
	// Since it will add if it is beneficial and subtract score and will block 
	int best_score = -1000;
	int best_col = 0;

	// Selects a col based off the best score of the each column
	for (int col = 1; col <= MAX_COL; col++)
	{
		// Using a temp_board to look at all the possible positions and scoring them to determine which is the best column
		char temp_board[MAX_ROW][MAX_COL];
		CopyArray(board, temp_board, MAX_ROW, MAX_COL);
		// DropChip will change the index from 1-7 to 0-6
		DropChip(temp_board, col, chip);
		int score = score_col(temp_board, chip);

		// if the best score is on a column that is full it will set the score to 0

		// Prevents infinite loop
		if (isColumnFull(temp_board, col))
			score = 0;

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
	col--;
	for (int i = MAX_ROW - 1; i >= 0; i--)
	{
		if (board[i][col] == EMPTY)
		{
			board[i][col] = chip;
			break;
		}
	}
}

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

	const int ROW_BOUND = 2; 
	const int COL_BOUND = 3;
	// Counts Diagonal Chips for each player
	// From left side (Negative Slope \) 
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		for (int col = MAX_COL - 1; col >= 0; col--)
		{
			// Cannot be less than ROWBOUND(2) & COLBOUND(3) BC when it is passed those, a connect 4 in a row is no longer possible
			if (row > ROW_BOUND && col >= COL_BOUND)
			{
				for (int i = 0; i < WINCOUNT; i++)
					if (board[row - i][col - i] == piece)
						piece_count++;
			
				if (piece_count >= WINCOUNT)
				{
					//player_win = true;
					cout << "  Left Diagonal Win "; 
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

	// From Right side (Positive Slope /)
	for (int row = MAX_ROW - 1; row >= 0; row--)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			// Cannot be less than ROWBOUND(2) & COLBOUND(3) BC when it is passed those, a connect 4 in a row is no longer possible
			if (row > ROW_BOUND && col <= COL_BOUND)
			{
				for (int i = 0; i < WINCOUNT; i++)
					if (board[row - i][col + i] == piece)
						piece_count++;

				if (piece_count >= WINCOUNT)
				{
					//player_win = true;
					cout << "   Right Diagonal Win " << piece << endl;
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

	if (isBoardFull(board))
		return true; 

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
	cout << "Would you like to play again?(Y/N): ";
	string ans; 
	getline(cin, ans);

	cout << endl;

	return (tolower(ans[0]) == 'y');
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

	int count = 0;

	for (int i = 0; i < v.size(); i++)
	{
		if (v.at(i) == chip)
			count++;
	}

	return count;
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