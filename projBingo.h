//Katherine Lawler
//Bingo Card Header File
//Start Date: 5/19/2025
//Last Updated: 8/15/2025
//Description: This file contains the function prototypes and constants for the bingo card structure.

#ifndef PROJBINGO_H
#define PROJBINGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <ctype.h>

#define ROWS 5
#define COLS 5
#define BALLS 75
enum Columns { B = 0, I, N, G, O };

typedef struct _bingoCard {
    int card[ROWS][COLS];
    int marked[ROWS][COLS];
    int expectedMarked[ROWS][COLS];
    int numMarked;
    int expectedNumMarked;
    int bingo;
} bingoCard;
typedef struct _computerCard {
    int card[ROWS][COLS];
    int expectedMarked[ROWS][COLS];
    int expectedNumMarked;
    int bingo;
} computerCard;

// Function prototypes
void initializeColumn(int card [ROWS][COLS], int col, int min, int max);
void initializeCard(int card [ROWS][COLS]);
void printCard(bingoCard *card);
int randomNumber(int min, int max);
int testRepeat(int card [ROWS][COLS] , int row, int col, int newNum);
void printCard(bingoCard *card);
void markSpace(bingoCard *card, int row, int col);
void beginDisplay(bingoCard *card);
void autoDaubCheck(bingoCard *card, int ballNum);
int bingoCheck(int card[ROWS][COLS]);
void printCardNC(bingoCard *card, WINDOW *win);
bingoCard *createCard();
computerCard *createComputerCard();

#endif // PROJBINGO_H