#ifndef __CELL_INCLUDED__
#define __CELL_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct cell CELL;

extern CELL *newCELL(int row, int col);
extern int getRowCELL(CELL *cell);
extern int getColCELL(CELL *cell);
extern char getValCELL(CELL *cell);
extern bool getBottomCELL(CELL *cell);
extern bool getRightCELL(CELL *cell);
extern void setRowCELL(CELL *cell, int row);
extern void setColCELL(CELL *cell, int col);
extern void setValCELL(CELL *cell, char val);
extern void setBottomCELL(CELL *cell, bool bot);
extern void setRightCELL(CELL *cell, bool rig);

#endif
