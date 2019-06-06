#pragma once

const int MAX_ROW = 6;
const int MAX_COL = 7;
const int WIN_CONNECT = 4; 

const int GREEN = 10;
const int YELLOW = 14;
const int RED = 12;
const int BLUE = 9;
const int WHITE = 15;

const char PLAYERCHIP = 'O';
const char BOTCHIP = '0';
const char EMPTY = ' ';

void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole);

// Starts the game loop
void StartGame(char board[][MAX_COL], HANDLE &hConsole);

// Prints who won, lost, or tied
void DeclareWinner(const char board[][MAX_COL], HANDLE &hConsole);

// Checks if a player has won, connected 4 chips
bool EndGame(const char board[][MAX_COL], char piece);

// AI
void BOT(char board[][MAX_COL]);

// Ask for column from the user or if it is the bot's chip calls the AI to select the best column
void GameInput(char board[][MAX_COL], char chip);

// Checks if the column is full
bool isColumnFull(const char board[][MAX_COL], int column_pick);

// Scores each column using a hypothetical temp board to allow the bot to see what is the best column choice.
// Picks the best score which corresponds to the column and returns it. 
int PickBestCol(char board[][MAX_COL], char chip);

// Sets the bottom most empty row of a column to a the chip (char)
void DropChip(char temp_board[][MAX_COL], int col, char chip);

// Checks if the board is full, used to determine a tie
bool isBoardFull(const char board[][MAX_COL]);

// Clears the screen
void clrscr();

// Fills an array with a character
void fillA(char a[MAX_ROW][MAX_COL], char ch);

// Scores the column by taking each column and taking 4 cells and scoring them based off what is the best outcome
// Checks hortizonal, vertical, and diagonals to returns the score for the column
int score_col(const char board[][MAX_COL], char chip);

// Scores the a vector of 4 chips
int ScoreWindow(std::vector<char> window, char chip);

// Counts the amount of occurances of a chip(char) in a vector
int CountChar(std::vector<char> v, char chip);

// Creates a copy of an array to a different memory address
void CopyArray(const char a1[][MAX_COL], char a2[][MAX_COL], int row_size, int col_size);

// Asks if the user wants to play again
bool RunAgain();