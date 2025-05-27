//Katherine Lawler
//Bingo Game Header File
//Start Date: 5/20/2025
//Last Updated: 5/20/2025
//Description: This file contains the function prototypes and constants for the bingo game structure.

#ifndef PROJBINGOGAME_H
#define PROJBINGOGAME_H

#include "projBingo.h"

typedef struct _bingoGame {
    int balls[BALLS];
    int numCalls;
} bingoGame;

// Function prototypes
void initializeGame(bingoGame *game);
void printCall(int ballNum);
void callBall(bingoGame * game);
void printCalls(bingoGame *game);
bingoGame *createGame();
int daubSpace(bingoCard *card);
int gamePlay();

#endif // PROJBINGOGAME_H