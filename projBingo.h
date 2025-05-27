//Katherine Lawler
//Bingo Card Header File
//Start Date: 5/19/2025
//Last Updated: 5/20/2025
//Description: This file contains the function prototypes and constants for the bingo card structure.

#ifndef PROJBINGO_H
#define PROJBINGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

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

// Function prototypes
void initializeColumn(bingoCard * card, int col, int min, int max);
void initializeCard(bingoCard *card);
void printCard(bingoCard *card);
int randomNumber(int min, int max);
int testRepeat(bingoCard *card , int row, int col, int newNum);
void printCard(bingoCard *card);
void markSpace(bingoCard *card, int row, int col);
void beginDisplay(bingoCard *card);
void printCardNC(bingoCard *card, WINDOW *win);
bingoCard *createCard();

#endif // PROJBINGO_H