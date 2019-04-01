//Author: Williams Beaumont
//Purpose: Class implementing a board for the game

#include "board.h"
#include "cell.h"
#include "stack.h"
#include "da.h"
#include "queue.h"
#include "cda.h"

//Structure of the board
typedef struct board {
  int rows;
  int columns;
  CELL ***cells;
} BOARD;

//Constructor for a board
BOARD *newBOARD(int row, int col) {
  BOARD *board = malloc(sizeof(BOARD));
  board->rows = row;
  board->columns = col;
  board->cells = malloc(sizeof(CELL **) * board->rows);
  int i = 0;
  int j = 0;
  for (i = 0; i < board->rows; i = i + 1) {
    board->cells[i] = malloc(sizeof(CELL *) * board->columns);
    for (j = 0; j < board->columns; j = j + 1) {
      board->cells[i][j] = newCELL(i, j);
    }
  }
  return board;
}

//Function allowing user to get the rows of the board
int getRowBOARD(BOARD *board) {
  return board->rows;
}

//Function allowing user to get the columns of the board
int getColBOARD(BOARD *board) {
  return board->columns;
}

//Function allowing user to set the rows of the board
void setRowBOARD(BOARD *board, int row) {
  board->rows = row;
}

//Function allowing user to set the columns of the board
void setColBOARD(BOARD *board, int col) {
  board->columns = col;
}

//Function allowing user to get cell at certain coordinates
CELL *getCell(BOARD *board, int row, int col) {
  return board->cells[row][col];
}

//Function allowing user to get cell to the left of a certain cell
CELL *getCellLeft(BOARD *board, CELL *cell) {
  if (getColCELL(cell) != 0)
    return getCell(board, getRowCELL(cell), getColCELL(cell) - 1);
  else
    return NULL;
}

//Function allowing user to get cell to the right of a certain cell
CELL *getCellRight(BOARD *board, CELL *cell) {
  if (getColCELL(cell) != getColBOARD(board) - 1)
    return getCell(board, getRowCELL(cell), getColCELL(cell) + 1);
  else
    return NULL;
}

//Function allowing user to get cell above a certain cell
CELL *getCellTop(BOARD *board, CELL *cell) {
  if (getRowCELL(cell) != 0)
    return getCell(board, getRowCELL(cell) - 1, getColCELL(cell));
  else
    return NULL;
}

//Function allowing user to get cell below a certain cell
CELL *getCellBottom(BOARD *board, CELL *cell) {
  if (getRowCELL(cell) != getRowBOARD(board) - 1)
    return getCell(board, getRowCELL(cell) + 1, getColCELL(cell));
  else
    return NULL;
}

//Function to display the board
void displayBOARD(BOARD *board) {
  int i = 0;
  int j = 0;

  //printing number labels for each column of the board
  printf("\n ");
  for (i = 0; i < getColBOARD(board); i = i + 1) {
    if (i < 8)
      printf(" %d  ", i + 1);
    else if (i < 98)
      printf(" %d ", i + 1);
    else if (i < 998)
      printf(" %d", i + 1);
  }
  printf("\n");

  //printing top line of dashes
  for (i = 0; i < (getColBOARD(board) * 4) + 1; i = i + 1)
    printf("-");
  printf("\n");

  //printing each cell
  for (i = 0; i < getRowBOARD(board); i = i + 1) {
    for (j = 0; j < getColBOARD(board); j = j + 1) {
      //printing left edge of board
      if (j == 0)
        printf("|");
      //printing value of each cell
      printf(" %c |", getValCELL(getCell(board, i, j)));
    }
    //printing bottom wall of each cell
    printf("\n");
    for (j = 0; j < (getColBOARD(board) * 4) + 1; j = j + 1)
      printf("-");
    //transitioning to next row of cells
    printf("\n");
  }

  //printing number labels for each column of the board
  printf(" ");
  for (i = 0; i < getColBOARD(board); i = i + 1) {
    if (i < 8)
      printf(" %d  ", i + 1);
    else if (i < 98)
      printf(" %d ", i + 1);
    else if (i < 1000)
      printf(" %d", i + 1);
    else
      printf("%d", i + 1);
  }
  printf("\n\n");
}

//Function to free the board
void freeBOARD(BOARD *board) {
  int i = 0;
  int j = 0;
  for (i = 0; i < getRowBOARD(board); i = i + 1) {
    for (j = 0; j < getColBOARD(board); j = j + 1)
      free(board->cells[i][j]);
  }
  for (i = 0; i < getRowBOARD(board); i = i + 1)
    free(board->cells[i]);
  free(board->cells);
  free(board);
}
