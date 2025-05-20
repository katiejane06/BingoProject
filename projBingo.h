//Katherine Lawler
//Bingo Card Header File
//Start Date: 5/19/2025
//Last Updated: 5/19/2025
//Description: This file contains the function prototypes and constants for the bingo card program.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#defind BALLS 74

typedef struct _bingoCard {
    int card[ROWS][COLS];
    int marked[ROWS][COLS];
    int numMarked;
    int expectedNumMarked;
    int bingo;
} bingoCard;


void initializeColumn(bingoCard * card, int col, int min, int max);
void initializeCard(bingoCard *card);
void printCard(bingoCard *card);
int randomNumber(int min, int max);
int testRepeat(bingoCard, int row, int col, int newNum);