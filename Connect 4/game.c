//Author: Williams Beaumont
//Purpose: Class implementing functions for single player gameplay
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "integer.h"

//function that checks if four of player 1's pieces are in a row
bool connected1(CELL *cell, BOARD *board) {
  //vertical row check
  int inARow = 0;
  int i = 0;
  int j = 0;
  while (inARow < 4 && i < getRowBOARD(board)) {
    if (getValCELL(getCell(board, i, getColCELL(cell))) == 'X')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
  }
  if (inARow == 4)
    return true;

  //horizontal row check
  inARow = 0;
  i = 0;
  while (inARow < 4 && i < getColBOARD(board)) {
    if (getValCELL(getCell(board, getRowCELL(cell), i)) == 'X')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
  }
  if (inARow == 4)
    return true;

  //left diagonal check
  inARow = 0;
  i = getRowCELL(cell);
  j = getColCELL(cell);
  while (i > 0 && j > 0) {
    i = i - 1;
    j = j - 1;
  }
  while (inARow < 4 && i < getRowBOARD(board) && j < getColBOARD(board)) {
    if (getValCELL(getCell(board, i, j)) == 'X')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
    j = j + 1;
  }
  if (inARow == 4)
    return true;

  //right diagonal check
  inARow = 0;
  i = getRowCELL(cell);
  j = getColCELL(cell);
  while (i > 0 && j < getColBOARD(board) - 1) {
    i = i - 1;
    j = j + 1;
  }
  while (inARow < 4 && i < getRowBOARD(board) && j > -1) {
    if (getValCELL(getCell(board, i, j)) == 'X')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
    j = j - 1;
  }
  if (inARow == 4)
    return true;

  //if not connected
  return false;
}

//function that checks if four of player 2 or the computer's pieces are in a row
bool connected2(CELL *cell, BOARD *board) {
  //vertical row check
  int inARow = 0;
  int i = 0;
  while (inARow < 4 && i < getRowBOARD(board)) {
    if (getValCELL(getCell(board, i, getColCELL(cell))) == 'O')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
  }
  if (inARow == 4)
    return true;

  //horizontal row check
  inARow = 0;
  i = 0;
  while (inARow < 4 && i < getColBOARD(board)) {
    if (getValCELL(getCell(board, getRowCELL(cell), i)) == 'O')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
  }
  if (inARow == 4)
    return true;

  //left diagonal check
  inARow = 0;
  i = getRowCELL(cell);
  int j = getColCELL(cell);
  while (i > 0 && j > 0) {
    i = i - 1;
    j = j - 1;
  }
  while (inARow < 4 && i < getRowBOARD(board) && j < getColBOARD(board)) {
    if (getValCELL(getCell(board, i, j)) == 'O')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
    j = j + 1;
  }
  if (inARow == 4)
    return true;

  //right diagonal check
  inARow = 0;
  i = getRowCELL(cell);
  j = getColCELL(cell);
  while (i > 0 && j < getColBOARD(board) - 1) {
    i = i - 1;
    j = j + 1;
  }
  while (inARow < 4 && i < getRowBOARD(board) && j > -1) {
    if (getValCELL(getCell(board, i, j)) == 'O')
      inARow = inARow + 1;
    else
      inARow = 0;

    i = i + 1;
    j = j - 1;
  }
  if (inARow == 4)
    return true;

  //if not connected
  return false;
}

void tied(BOARD *board, int *win) {
  int i = 0;
  bool tie = true;
  for (i = 0; i < getColBOARD(board); i = i + 1) {
    if (getValCELL(getCell(board, 0, i)) == ' ')
      tie = false;
  }
  if (tie == true) {
    printf("It's a tie!\n");
    *win = *win + 1;
  }
}

//function that runs a single turn for first player
void player1Turn(BOARD *board, int *win, int *player1wins) {
  //player chooses a column to drop a piece into

  int colNum = 0;
  char conversionString[6];
  char cleanup = ' ';
  printf("(Player 1) Enter column number: ");
  fgets(conversionString, 6, stdin);
  colNum = atoi(conversionString);
  if (colNum < 1 || colNum > getColBOARD(board) || (colNum > 0 && colNum < getColBOARD(board) + 1 && getValCELL(getCell(board, 0, colNum - 1)) != ' ')) {
    while (colNum < 1 || colNum > getColBOARD(board) || (colNum > 0 && colNum < getColBOARD(board) + 1 && getValCELL(getCell(board, 0, colNum - 1)) != ' ')) {
      if (conversionString[strlen(conversionString) - 1] != '\n') {
        cleanup = ' ';
        while (cleanup != '\n') {
          scanf("%1c", &cleanup);
        }
      }
      printf("Invalid column. Please enter a column between 1 and %d that is not already full.", getColBOARD(board));
      printf("\n(Player 1) Enter column number: ");
      fgets(conversionString, 6, stdin);
      colNum = atoi(conversionString);
    }
  }
  colNum = colNum - 1;

  //piece is placed into the board
  int rowNum = 0;
  while (getValCELL(getCell(board, rowNum + 1, colNum)) == ' ' && rowNum < getRowBOARD(board) - 2) {
    rowNum = rowNum + 1;
  }
  if (getValCELL(getCell(board, getRowBOARD(board) - 1, colNum)) == ' ')
    rowNum = getRowBOARD(board) - 1;

  setValCELL(getCell(board, rowNum, colNum), 'X');

  displayBOARD(board);

  //check for win condition
  if (connected1(getCell(board, rowNum, colNum), board) == true) {
    printf("Player 1 Wins! (Total Score: %d)\n", *player1wins);
    *win = *win + 1;
    *player1wins = *player1wins + 1;
  }
  tied(board, win);
}

//function that runs a single turn for second player
void player2Turn(BOARD *board, int *win, int *player2wins) {
  //player chooses a column to drop a piece into

  int colNum = 0;
  char conversionString[6];
  char cleanup = ' ';
  printf("(Player 2) Enter column number: ");
  fgets(conversionString, 6, stdin);
  colNum = atoi(conversionString);
  if (colNum < 1 || colNum > getColBOARD(board) || (colNum > 0 && colNum < getColBOARD(board) + 1 && getValCELL(getCell(board, 0, colNum - 1)) != ' ')) {
    while (colNum < 1 || colNum > getColBOARD(board) || (colNum > 0 && colNum < getColBOARD(board) + 1 && getValCELL(getCell(board, 0, colNum - 1)) != ' ')) {
      if (conversionString[strlen(conversionString) - 1] != '\n') {
        cleanup = ' ';
        while (cleanup != '\n') {
          scanf("%1c", &cleanup);
        }
      }
      printf("Invalid column. Please enter a column between 1 and %d.", getColBOARD(board));
      printf("\n(Player 2) Enter column number: ");
      fgets(conversionString, 6, stdin);
      colNum = atoi(conversionString);
    }
  }
  colNum = colNum - 1;

  //piece is placed into the board
  int rowNum = 0;
  while (getValCELL(getCell(board, rowNum + 1, colNum)) == ' ' && rowNum < getRowBOARD(board) - 2) {
    rowNum = rowNum + 1;
  }
  if (getValCELL(getCell(board, getRowBOARD(board) - 1, colNum)) == ' ')
    rowNum = getRowBOARD(board) - 1;

  setValCELL(getCell(board, rowNum, colNum), 'O');

  displayBOARD(board);

  //check for win condition
  if (connected2(getCell(board, rowNum, colNum), board) == true) {
    printf("Player 2 Wins! (Total Score: %d)\n", *player2wins);
    *win = *win + 1;
    *player2wins = *player2wins + 1;
  }
  tied(board, win);
}

//function that runs a single turn for the computer
void computerTurn(BOARD *board, int *win, int *player2wins) {
  //computer chooses a column to drop a piece into
  int colNum = 0;
  int rowNum = 0;
  DA *da = newDA();
  setDAfree(da, freeINTEGER);

  //check each column to see if the top piece in that column is an X
  for (colNum = 0; colNum < getColBOARD(board); colNum = colNum + 1) {
    while (getValCELL(getCell(board, rowNum, colNum)) == ' ' && rowNum < getRowBOARD(board) - 1)
      rowNum = rowNum + 1;

    //add columns of adjacent empty cells into array of possible choices
    if (getValCELL(getCell(board, rowNum, colNum)) == 'X') {
      //check for empty space above X piece
      if (rowNum != 0)
        insertDAback(da, newINTEGER(colNum));

      //check for empty space to the left of X piece
      if (colNum != 0 && getValCELL(getCellLeft(board, getCell(board, rowNum, colNum))) == ' ') {
        if (rowNum == getRowBOARD(board) - 1)
          insertDAback(da, newINTEGER(colNum - 1));
        else if (getValCELL(getCellBottom(board, getCellLeft(board, getCell(board, rowNum, colNum)))) != ' ')
          insertDAback(da, newINTEGER(colNum - 1));
      }

      //check for empty space to the right of X piece
      if (colNum != getColBOARD(board) - 1 && getValCELL(getCellRight(board, getCell(board, rowNum, colNum))) == ' ') {
        if (rowNum == getRowBOARD(board) - 1)
          insertDAback(da, newINTEGER(colNum + 1));
        else if (getValCELL(getCellBottom(board, getCellRight(board, getCell(board, rowNum, colNum)))) != ' ')
          insertDAback(da, newINTEGER(colNum + 1));
      }
    }
  }
  colNum = getINTEGER((INTEGER *) getDA(da, rand() % sizeDA(da)));
  freeDA(da);

  //piece is placed into the board
  rowNum = 0;
  while (getValCELL(getCell(board, rowNum + 1, colNum)) == ' ' && rowNum < getRowBOARD(board) - 2) {
    rowNum = rowNum + 1;
  }
  if (getValCELL(getCell(board, getRowBOARD(board) - 1, colNum)) == ' ')
    rowNum = getRowBOARD(board) - 1;

  setValCELL(getCell(board, rowNum, colNum), 'O');

  displayBOARD(board);

  //check for win condition
  if (connected2(getCell(board, rowNum, colNum), board) == true) {
    printf("The Computer Wins! (Total Score: %d)\n", *player2wins);
    *win = *win + 1;
    *player2wins = *player2wins + 1;
  }
  tied(board, win);
}

//function that incorporates previous ones into a playable version
void runSingle(int *player1wins, int *player2wins) {
  //print size menu display
  printf("\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
  printf("*        _ _ _ _   _ _ _ _   _     _   _     _   _ _ _ _   _ _ _ _   _ _ _ _     _   _      *\n");
  printf("*      / _ _ _ / /  _ _  / /  |  / / /  |  / / / _ _ _ / / _ _ _ / /_    _ /   / /_/ /_     *\n");
  printf("*     / /       / /   / / /   | / / /   | / / / /_ _ _  / /         /   /     /_ _  _ /     *\n");
  printf("*    / / _ _   / / _ / / / /|    / / /|    / / /_ _ _  / / _ _     /   /         / /        *\n");
  printf("*   / _ _ _ / / _ _ _ / /_/ | _ / /_/ | _ / / _ _ _ / / _ _ _ /   / _ /         /_/         *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                              (Single Player) Select board size:                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                     Standard  |  Custom                                   *\n");
  printf("*                                                                                           *\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

  //read the input from user to determine board size
  char mode[10];
  char cleanup = ' ';
  fgets(mode, 10, stdin);
  if (strncmp(mode, "standard", 8) != 0 && strncmp(mode, "Standard", 8) != 0 && strncmp(mode, "custom", 6) != 0 && strncmp(mode, "Custom", 6) != 0) {
    while (strncmp(mode, "standard", 8) != 0 && strncmp(mode, "Standard", 8) != 0 && strncmp(mode, "custom", 6) != 0 && strncmp(mode, "Custom", 6) != 0) {
      if (mode[strlen(mode) - 1] != '\n') {
        cleanup = ' ';
        while (cleanup != '\n') {
          scanf("%1c", &cleanup);
        }
      }
      printf("Invalid choice. Please choose one of the listed options.\n");
      fgets(mode, 10, stdin);
    }
  }

  //if standard size is chosen
  if (strncmp(mode, "standard", 8) == 0 || strncmp(mode, "Standard", 8) == 0) {
    BOARD *board = newBOARD(6, 7);
    displayBOARD(board);

    //begin game
    int win = 0;
    //until the win condition is met, the game will continue
    while (win == 0) {
      player1Turn(board, &win, player1wins);
      if (win == 0)
        computerTurn(board, &win, player2wins);
    }
    freeBOARD(board);
  }

  //if custom size is chosen
  else if (strncmp(mode, "custom", 6) == 0 || strncmp(mode, "Custom", 6) == 0) {
    int h = 0;
    int w = 0;
    char conversionString[6];

    cleanup = ' ';
    printf("\nEnter board height: ");
    fgets(conversionString, 6, stdin);
    h = atoi(conversionString);
    if (h < 4) {
      while (h < 4) {
        if (conversionString[strlen(conversionString) - 1] != '\n') {
          cleanup = ' ';
          while (cleanup != '\n') {
            scanf("%1c", &cleanup);
          }
        }
        printf("Invalid board height. Please enter a height greater than 3.");
        printf("\nEnter board height: ");
        fgets(conversionString, 6, stdin);
        h = atoi(conversionString);
      }
    }

    cleanup = ' ';
    printf("\nEnter board width: ");
    fgets(conversionString, 6, stdin);
    w = atoi(conversionString);
    if (w < 4) {
      while (w < 4) {
        if (conversionString[strlen(conversionString) - 1] != '\n') {
          cleanup = ' ';
          while (cleanup != '\n') {
            scanf("%1c", &cleanup);
          }
        }
        printf("Invalid board width. Please enter a width greater than 3.");
        printf("\nEnter board width: ");
        fgets(conversionString, 6, stdin);
        w = atoi(conversionString);
      }
    }

    BOARD *board = newBOARD(h, w);
    displayBOARD(board);
    //begin game
    int win = 0;
    //until the win condition is met, the game will continue
    while (win == 0) {
      player1Turn(board, &win, player1wins);
      if (win == 0)
        computerTurn(board, &win, player2wins);
    }
    freeBOARD(board);
  }

  //if players want to rematch
  printf("\nRematch? Yes / No: ");
  char rematch[5];
  cleanup = ' ';
  fgets(rematch, 5, stdin);
  if (strncmp(rematch, "yes", 3) != 0 && strncmp(rematch, "Yes", 3) != 0 && strncmp(rematch, "no", 2) != 0 && strncmp(rematch, "No", 2) != 0) {
    while (strncmp(rematch, "yes", 3) != 0 && strncmp(rematch, "Yes", 3) != 0 && strncmp(rematch, "no", 2) != 0 && strncmp(rematch, "No", 2) != 0) {
      if (rematch[strlen(rematch) - 1] != '\n') {
        cleanup = ' ';
        while (cleanup != '\n') {
          scanf("%1c", &cleanup);
        }
      }
      printf("Invalid choice. Please choose one of the listed options.\n");
      fgets(rematch, 5, stdin);
    }
  }

  if (strncmp(rematch, "yes", 3) == 0 || strncmp(rematch, "Yes", 3) == 0) {
    runSingle(player1wins, player2wins);
  }
  else if (strncmp(rematch, "no", 2) == 0 || strncmp(rematch, "No", 2) == 0) {
    printf("\nFinal Score\nPlayer 1: %d\nThe Computer: %d\n", *player1wins - 1, *player2wins - 1);
    if (*player1wins > *player2wins)
      printf("\nPlayer 1 had the most wins.\n");
    else if (*player1wins < *player2wins)
      printf("\nThe Computer had the most wins.\n");
    else
      printf("\nIt's a tie.\n");
    return;
  }
}

void runMulti(int *player1wins, int *player2wins) {
  //print size menu display
  printf("\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
  printf("*        _ _ _ _   _ _ _ _   _     _   _     _   _ _ _ _   _ _ _ _   _ _ _ _     _   _      *\n");
  printf("*      / _ _ _ / /  _ _  / /  |  / / /  |  / / / _ _ _ / / _ _ _ / /_    _ /   / /_/ /_     *\n");
  printf("*     / /       / /   / / /   | / / /   | / / / /_ _ _  / /         /   /     /_ _  _ /     *\n");
  printf("*    / / _ _   / / _ / / / /|    / / /|    / / /_ _ _  / / _ _     /   /         / /        *\n");
  printf("*   / _ _ _ / / _ _ _ / /_/ | _ / /_/ | _ / / _ _ _ / / _ _ _ /   / _ /         /_/         *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                (Multiplayer) Select board size:                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                     Standard  |  Custom                                   *\n");
  printf("*                                                                                           *\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

  //read the input from user to determine board size
  char mode[10];
  char cleanup = ' ';
  fgets(mode, 10, stdin);
  if (strncmp(mode, "standard", 8) != 0 && strncmp(mode, "Standard", 8) != 0 && strncmp(mode, "custom", 6) != 0 && strncmp(mode, "Custom", 6) != 0) {
    while (strncmp(mode, "standard", 8) != 0 && strncmp(mode, "Standard", 8) != 0 && strncmp(mode, "custom", 6) != 0 && strncmp(mode, "Custom", 6) != 0) {
      if (mode[strlen(mode) - 1] != '\n') {
        cleanup = ' ';
        while (cleanup != '\n') {
          scanf("%1c", &cleanup);
        }
      }
      printf("Invalid choice. Please choose one of the listed options.\n");
      fgets(mode, 10, stdin);
    }
  }

  //if standard size is chosen
  if (strncmp(mode, "standard", 8) == 0 || strncmp(mode, "Standard", 8) == 0) {
    BOARD *board = newBOARD(6, 7);
    displayBOARD(board);
    //begin game
    int win = 0;
    //until the win condition is met, the game will continue
    while (win == 0) {
      player1Turn(board, &win, player1wins);
      if (win == 0)
        player2Turn(board, &win, player2wins);
    }
    freeBOARD(board);
  }

  //if custom size is chosen
  else if (strncmp(mode, "custom", 6) == 0 || strncmp(mode, "Custom", 6) == 0) {
    int h = 0;
    int w = 0;
    char conversionString[6];

    cleanup = ' ';
    printf("\nEnter board height: ");
    fgets(conversionString, 6, stdin);
    h = atoi(conversionString);
    if (h < 4) {
      while (h < 4) {
        if (conversionString[strlen(conversionString) - 1] != '\n') {
          cleanup = ' ';
          while (cleanup != '\n') {
            scanf("%1c", &cleanup);
          }
        }
        printf("Invalid board height. Please enter a height greater than 3.");
        printf("\nEnter board height: ");
        fgets(conversionString, 6, stdin);
        h = atoi(conversionString);
      }
    }

    cleanup = ' ';
    printf("\nEnter board width: ");
    fgets(conversionString, 6, stdin);
    w = atoi(conversionString);
    if (w < 4) {
      while (w < 4) {
        if (conversionString[strlen(conversionString) - 1] != '\n') {
          cleanup = ' ';
          while (cleanup != '\n') {
            scanf("%1c", &cleanup);
          }
        }
        printf("Invalid board width. Please enter a width greater than 3.");
        printf("\nEnter board width: ");
        fgets(conversionString, 6, stdin);
        w = atoi(conversionString);
      }
    }

    BOARD *board = newBOARD(h, w);
    displayBOARD(board);
    //begin game
    int win = 0;
    //until the win condition is met, the game will continue
    while (win == 0) {
      player1Turn(board, &win, player1wins);
      if (win == 0)
        player2Turn(board, &win, player2wins);
    }
    freeBOARD(board);
  }

  //if players want to rematch
  printf("\nRematch? Yes / No: ");
  char rematch[5];
  cleanup = ' ';
  fgets(rematch, 5, stdin);
  if (strncmp(rematch, "yes", 3) != 0 && strncmp(rematch, "Yes", 3) != 0 && strncmp(rematch, "no", 2) != 0 && strncmp(rematch, "No", 2) != 0) {
    while (strncmp(rematch, "yes", 3) != 0 && strncmp(rematch, "Yes", 3) != 0 && strncmp(rematch, "no", 2) != 0 && strncmp(rematch, "No", 2) != 0) {
      if (rematch[strlen(rematch) - 1] != '\n') {
        cleanup = ' ';
        while (cleanup != '\n') {
          scanf("%1c", &cleanup);
        }
      }
      printf("Invalid choice. Please choose one of the listed options.\n");
      fgets(rematch, 5, stdin);
    }
  }

  if (strncmp(rematch, "yes", 3) == 0 || strncmp(rematch, "Yes", 3) == 0) {
    runMulti(player1wins, player2wins);
  }
  else if (strncmp(rematch, "no", 2) == 0 || strncmp(rematch, "No", 2) == 0) {
    printf("\nFinal Score\nPlayer 1: %d\nPlayer 2: %d\n", *player1wins - 1, *player2wins - 1);
    if (*player1wins > *player2wins)
      printf("\nPlayer 1 had the most wins.\n");
    else if (*player1wins < *player2wins)
      printf("\nPlayer 2 had the most wins.\n");
    else
      printf("\nIt's a tie.\n");
    return;
  }
}

void menu() {
  //print initial menu display
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
  printf("*        _ _ _ _   _ _ _ _   _     _   _     _   _ _ _ _   _ _ _ _   _ _ _ _     _   _      *\n");
  printf("*      / _ _ _ / /  _ _  / /  |  / / /  |  / / / _ _ _ / / _ _ _ / /_    _ /   / /_/ /_     *\n");
  printf("*     / /       / /   / / /   | / / /   | / / / /_ _ _  / /         /   /     /_ _  _ /     *\n");
  printf("*    / / _ _   / / _ / / / /|    / / /|    / / /_ _ _  / / _ _     /   /         / /        *\n");
  printf("*   / _ _ _ / / _ _ _ / /_/ | _ / /_/ | _ / / _ _ _ / / _ _ _ /   / _ /         /_/         *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                                                                           *\n");
  printf("*                                      Select game mode:                                    *\n");
  printf("*                                                                                           *\n");
  printf("*                                Single Player  |  Multiplayer                              *\n");
  printf("*                                                                                           *\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

  //read the input from user to determine game mode

  char mode[15];
  char cleanup = ' ';
  fgets(mode, 15, stdin);
  if (strncmp(mode, "single player", 13) != 0 && strncmp(mode, "Single Player", 13) != 0 && strncmp(mode, "multiplayer", 11) != 0 && strncmp(mode, "Multiplayer", 11) != 0) {
    while (strncmp(mode, "single player", 13) != 0 && strncmp(mode, "Single Player", 13) != 0 && strncmp(mode, "multiplayer", 11) != 0 && strncmp(mode, "Multiplayer", 11) != 0) {
      if (mode[strlen(mode) - 1] != '\n') {
          cleanup = ' ';
          while (cleanup != '\n') {
            scanf("%1c", &cleanup);
          }
      }
      printf("Invalid choice. Please choose one of the listed options.\n");
      fgets(mode, 15, stdin);
    }
  }

  int player1wins = 1;
  int player2wins = 1;
  //if single player is chosen
  if (strncmp(mode, "single player", 13) == 0 || strncmp(mode, "Single Player", 13) == 0)
    runSingle(&player1wins, &player2wins);
  //if multiplayer is chosen
  else if (strncmp(mode, "multiplayer", 11) == 0 || strncmp(mode, "Multiplayer", 11) == 0)
    runMulti(&player1wins, &player2wins);
}
