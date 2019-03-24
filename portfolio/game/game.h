#ifndef __GAME_INCLUDED__
#define __GAME_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include "board.h"

extern bool connected1(CELL *cell, BOARD *board);
extern bool connected2(CELL *cell, BOARD *board);
extern void player1Turn(BOARD *board, int *win, int *player1wins);
extern void player2Turn(BOARD *board, int *win, int *player2wins);
extern void computerTurn(BOARD *board, int *win);
extern void runSingle();
extern void runMulti(int *player1wins, int *player2wins);
extern void menu();

#endif
