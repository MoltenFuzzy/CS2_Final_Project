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

void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole);

void StartGame(char board[][MAX_COL], HANDLE &hConsole);

void DeclareWinner(const char board[][MAX_COL], HANDLE &hConsole);

bool EndGame(const char board[][MAX_COL], char piece);

void BOT(char board[][MAX_COL]);

void PutChip(char board[][MAX_COL], char chip);

bool isColumnFull(const char board[][MAX_COL], int column_pick);

//int Minimax(const char board[][MAX_COL], int depth, bool MaximizingPlayer);

int PickBestCol(char board[][MAX_COL], char chip);

void DropChip(char temp_board[][MAX_COL], int col, char chip);

bool isBoardFull(const char board[][MAX_COL]);

void clrscr();

void fillA(char a[MAX_ROW][MAX_COL], char ch);

std::vector<int> GetValidCols(const char board[][MAX_COL]);

int score_col(const char board[][MAX_COL], char chip);

int ScoreTheBoard(std::vector<char> window, char chip);

int get_next_open_row(const char board[][MAX_COL], int col);

bool IsValidXY(const char board[][MAX_COL], int col);

int CountChar(std::vector<char> v, char chip);

void CopyArray(const char a1[][MAX_COL], char a2[][MAX_COL], int row_size, int col_size);

bool RunAgain();