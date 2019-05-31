#pragma once

#include <iostream>
#include <windows.h>   // WinApi header
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime> 

const int MAX_ROW = 6;
const int MAX_COL = 7;

const int GREEN = 10;
const int YELLOW = 14;
const int RED = 12;
const int BLUE = 9;
const int WHITE = 15;

const char PLAYERCHIP = 'O';
const char BOTCHIP = '0';
const char BLANKSPACE = ' ';

void PrintBoard(const char board[][MAX_COL], HANDLE& hConsole);

void StartGame(char board[MAX_ROW][MAX_COL], bool &player_won, HANDLE &hConsole);

void DeclareWinner(const HANDLE &hConsole, bool player_won);

bool EndGame(const char board[][MAX_COL], bool& player_win);

void BOT(char board[][MAX_COL]);

void PutChip(char board[][MAX_COL], char chip, bool player = true);

void BOTAI(char board[][MAX_COL], int &column_pick);

bool isColumnFull(const char board[][MAX_COL], int column_pick);

int Minimax(const char board[][MAX_COL], int depth, bool MaximizingPlayer);

bool isBoardFull(const char board[][MAX_COL]);

void clrscr();

void fillA(char a[MAX_ROW][MAX_COL], char ch);

bool RunAgain();