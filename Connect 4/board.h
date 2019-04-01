#ifndef __BOARD_INCLUDED__
#define __BOARD_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "cell.h"
#include "stack.h"
#include "da.h"
#include "queue.h"
#include "cda.h"

typedef struct board BOARD;

extern BOARD *newBOARD(int row, int col);
extern int getRowBOARD(BOARD *board);
extern int getColBOARD(BOARD *board);
extern void setRowBOARD(BOARD *board, int row);
extern void setColBOARD(BOARD *board, int col);
extern CELL *getCell(BOARD *board, int row, int col);
extern CELL *getCellLeft(BOARD *board, CELL *cell);
extern CELL *getCellRight(BOARD *board, CELL *cell);
extern CELL *getCellTop(BOARD *board, CELL *cell);
extern CELL *getCellBottom(BOARD *board, CELL *cell);
extern void displayBOARD(BOARD *board);
extern void freeBOARD(BOARD *board);

#endif
