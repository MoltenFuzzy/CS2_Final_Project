#pragma once

#include <iostream>
#include <windows.h>   // winapi header
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime> 
#include <vector>

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

//Input: 
//Processing: 
//Output:
void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole);

//Input: 
//Processing: 
//Output:
void StartGame(char board[][MAX_COL], HANDLE &hConsole);

//Input: 
//Processing: 
//Output:
void DeclareWinner(const char board[][MAX_COL], HANDLE &hConsole);

//Input: 
//Processing: 
//Output:
bool EndGame(const char board[][MAX_COL], char piece);

//Input: 
//Processing: 
//Output:
void BOT(char board[][MAX_COL]);

//Input: 
//Processing: 
//Output:
void PutChip(char board[][MAX_COL], char chip);

//Input: 
//Processing: 
//Output:
bool isColumnFull(const char board[][MAX_COL], int column_pick);

//Input: 
//Processing: 
//Output:
int PickBestCol(char board[][MAX_COL], char chip);

//Input: 
//Processing: 
//Output:
void DropChip(char temp_board[][MAX_COL], int col, char chip);

//Input: 
//Processing: 
//Output:
bool isBoardFull(const char board[][MAX_COL]);

//Input: 
//Processing: 
//Output:
void clrscr();

//Input: 
//Processing: 
//Output:
void fillA(char a[MAX_ROW][MAX_COL], char ch);

//Input: 
//Processing: 
//Output:
std::vector<int> GetValidCols(const char board[][MAX_COL]);

//Input: 
//Processing: 
//Output:
int score_col(const char board[][MAX_COL], char chip);

//Input: 
//Processing: 
//Output:
int ScoreTheBoard(std::vector<char> window, char chip);

//Input: 
//Processing: 
//Output:
int get_next_open_row(const char board[][MAX_COL], int col);

//Input: 
//Processing: 
//Output:
bool IsValidXY(const char board[][MAX_COL], int col);

//Input: 
//Processing: 
//Output:
int CountChar(std::vector<char> v, char chip);

//Input: 
//Processing: 
//Output:
void CopyArray(const char a1[][MAX_COL], char a2[][MAX_COL], int row_size, int col_size);

//Input: 
//Processing: 
//Output:
bool RunAgain();