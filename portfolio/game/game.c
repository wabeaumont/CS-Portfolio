//Author: Williams Beaumont
//Purpose: Class implementing functions for single player gameplay
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include "board.h"

//function that checks if four of player 1's pieces are in a row
bool connected1(CELL *cell, BOARD *board) {
  //vertical row check
  /*if (getValCELL(getCellBottom(board, cell)) == 'X' && getValCELL(getCellBottom(board, getCellBottom(board, cell))) == 'X' && getValCELL(getCellBottom(board, getCellBottom(board, getCellBottom(board, cell)))) == 'X')
    return true;*/
  int inARow = 0;
  int i = 0;
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
  int j = getColCELL(cell);
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
  /*if (getValCELL(getCellBottom(board, cell)) == 'O' && getValCELL(getCellBottom(board, getCellBottom(board, cell))) == 'O' && getValCELL(getCellBottom(board, getCellBottom(board, getCellBottom(board, cell)))) == 'O')
    return true;*/
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

//function that runs a single turn for first player
void player1Turn(BOARD *board, int *win, int *player1wins) {
  //player chooses a column to drop a piece into
  int colNum = 0;
  printf("(Player 1) Enter column number: ");
  scanf("%d", &colNum);
  if (colNum < 1 || colNum > getColBOARD(board)) {
    while (colNum < 1 || colNum > getColBOARD(board)) {
      printf("Invalid column. Please enter a column between 1 and %d.", getColBOARD(board));
      printf("\n(Player 1) Enter column number: ");
      scanf("%d", &colNum);
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
}

//function that runs a single turn for second player
void player2Turn(BOARD *board, int *win, int *player2wins) {
  //player chooses a column to drop a piece into
  int colNum = 0;
  printf("(Player 2) Enter column number: ");
  scanf("%d", &colNum);
  if (colNum < 1 || colNum > getColBOARD(board)) {
    while (colNum < 1 || colNum > getColBOARD(board)) {
      printf("Invalid column. Please enter a column between 1 and %d.", getColBOARD(board));
      printf("\n(Player 2) Enter column number: ");
      scanf("%d", &colNum);
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
}

//function that runs a single turn for the computer
void computerTurn(BOARD *board, int *win, int *player2wins) {
  /*//computer chooses a column to drop a piece into


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
  }*/
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
  char mode[8];
  scanf("%[^\n]%*c", mode);

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
  }
  //if custom size is chosen
  else if (strncmp(mode, "custom", 8) == 0 || strncmp(mode, "Custom", 8) == 0) {
    int h = 0;
    int w = 0;
    printf("\nEnter board height: ");
    scanf("%d", &h);
    if (h < 4) {
      while (h < 4) {
        printf("Invalid board height. Please enter a height greater than 3.");
        printf("\nEnter board height: ");
        scanf("%d", &h);
      }
    }
    printf("Enter board width: ");
    scanf("%d", &w);
    if (w < 4) {
      while (w < 4) {
        printf("Invalid board width. Please enter a width greater than 3.");
        printf("\nEnter board width: ");
        scanf("%d", &w);
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
  }
  //if players wish to rematch
  char rematch;
  printf("\nRematch? Y/N ");
  scanf("%1c", &rematch);
  scanf("%1c", &rematch);
  if (rematch == 'Y' || rematch == 'y') {
    scanf("%1c", &rematch);
    runSingle(player1wins, player2wins);
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
  char mode[8];
  scanf("%[^\n]%*c", mode);
  if (strncmp(mode, "standard", 8) != 0 && strncmp(mode, "Standard", 8) != 0 && strncmp(mode, "custom", 8) != 0 && strncmp(mode, "Custom", 8) != 0) {
    while (strncmp(mode, "standard", 8) != 0 && strncmp(mode, "Standard", 8) != 0 && strncmp(mode, "custom", 8) != 0 && strncmp(mode, "Custom", 8) != 0) {
      printf("Invalid choice. Please choose one of the listed options.\n");
      scanf("%[^\n]%*c", mode);
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
  }
  //if custom size is chosen
  else if (strncmp(mode, "custom", 8) == 0 || strncmp(mode, "Custom", 8) == 0) {
    int h = 0;
    int w = 0;
    printf("\nEnter board height: ");
    scanf("%d", &h);
    if (h < 4) {
      while (h < 4) {
        printf("Invalid board height. Please enter a height greater than 3.");
        printf("\nEnter board height: ");
        scanf("%d", &h);
      }
    }
    printf("Enter board width: ");
    scanf("%d", &w);
    if (w < 4) {
      while (w < 4) {
        printf("Invalid board width. Please enter a width greater than 3.");
        printf("\nEnter board width: ");
        scanf("%d", &w);
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
  }
  //if players wish to rematch
  char rematch;
  printf("\nRematch? Y/N ");
  scanf("%1c", &rematch);
  scanf("%1c", &rematch);
  if (rematch == 'Y' || rematch == 'y') {
    scanf("%1c", &rematch);
    runMulti(player1wins, player2wins);
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
  char mode[13];
  scanf("%[^\n]%*c", mode);
  if (strncmp(mode, "single player", 13) != 0 && strncmp(mode, "Single Player", 13) != 0 && strncmp(mode, "multiplayer", 13) != 0 && strncmp(mode, "Multiplayer", 13) != 0) {
    while (strncmp(mode, "single player", 13) != 0 && strncmp(mode, "Single Player", 13) != 0 && strncmp(mode, "multiplayer", 13) != 0 && strncmp(mode, "Multiplayer", 13) != 0) {
      printf("Invalid choice. Please choose one of the listed options.\n");
      scanf("%[^\n]%*c", mode);
    }
  }

  int player1wins = 1;
  int player2wins = 1;
  //if single player is chosen
  if (strncmp(mode, "single player", 13) == 0 || strncmp(mode, "Single Player", 13) == 0)
    runSingle(&player1wins, &player2wins);
  //if multiplayer is chosen
  else if (strncmp(mode, "multiplayer", 13) == 0 || strncmp(mode, "Multiplayer", 13) == 0)
    runMulti(&player1wins, &player2wins);
}
