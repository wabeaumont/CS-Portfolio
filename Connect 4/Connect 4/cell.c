//Author: Williams Beaumont
//Purpose: Class implementing a cell for the game

#include "cell.h"

//Structure of the cell
typedef struct cell {
  int row;
  int column;
  char value;
  bool bottomEdge;
  bool rightEdge;
} CELL;

//Constructor for a new cell
CELL *newCELL(int row, int col) {
  CELL *cell = malloc(sizeof(CELL));
  cell->row = row;
  cell->column = col;
  cell->value = ' ';
  cell->bottomEdge = true;
  cell->rightEdge = true;
  return cell;
}

//Function allowing user to get the row of a cell
int getRowCELL(CELL *cell) {
  return cell->row;
}

//Function allowing user to get the column of a cell
int getColCELL(CELL *cell) {
  return cell->column;
}

//Function allowing user to get the value of a cell
char getValCELL(CELL *cell) {
  return cell->value;
}

//Function allowing user to get the bottomEdge status of a cell
bool getBottomCELL(CELL *cell) {
  return cell->bottomEdge;
}

//Function allowing user to get the rightEdge status of a cell
bool getRightCELL(CELL *cell) {
  return cell->rightEdge;
}

//Function allowing user to set the row of a cell
void setRowCELL(CELL *cell, int row) {
  cell->row = row;
}

//Function allowing user to set the column of a cell
void setColCELL(CELL *cell, int col) {
  cell->column = col;
}

//Function allowing user to set the value of a cell
void setValCELL(CELL *cell, char val) {
  cell->value = val;
}

//Function allowing user to set the bottomEdge status of a cell
void setBottomCELL(CELL *cell, bool bot) {
  cell->bottomEdge = bot;
}

//Function allowing user to set the rightEdge status of a cell
void setRightCELL(CELL *cell, bool rig) {
  cell->rightEdge = rig;
}
