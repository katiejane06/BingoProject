#include "projBingo.h"

int testRepeat(bingoCard *card, int row, int col, int newNum) {
    //check if the number is already in the card
    for (int i = 0; i < ROWS; i++) {
        if(card->card[i][col] == newNum)
            return 1; // number already exists in the column
    }
    return 0; // number does not exist in the card
}

int randomNumber(int min, int max) {
    // Generate a random number between min and max
    return (rand() % (max - min + 1)) + min;
}

void initializeColumn(bingoCard * card, int col, int min, int max)
{
    // Initialize a column with random numbers between min and max
    for (int i = 0; i < ROWS; i++) {
        int newNum;
        do {
            newNum = randomNumber(min, max);
        } while (testRepeat(card, i, col, newNum));
        card->card[i][col] = newNum;
    }
}

void initializeCard(bingoCard *card) {
    // Initialize the card with random numbers column by column
    initializeColumn(card, 0, 1, 15);
    initializeColumn(card, 1, 16, 30);
    initializeColumn(card, 2, 31, 45);
    initializeColumn(card, 3, 46, 60);
    initializeColumn(card, 4, 61, 75);
    // Set the center space to 0 (free space)
    card->card[2][2] = 0;
}

bingoCard *createCard() {
    // Allocate memory for a new bingo card
    bingoCard *card = (bingoCard *)malloc(sizeof(bingoCard));
    if (card == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Initialize the card
    initializeCard(card);
    // Initialize the marked array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            card->marked[i][j] = 0;
            card->expectedMarked[i][j] = 0; // Mark all spaces as unmarked
        }
    }
    card->marked[2][2] = 1; // Mark the free space
    card->expectedMarked[2][2] = 1; // Mark the free space as expected
    // Initialize other fields
    card->numMarked = 1;
    card->expectedNumMarked = 1;
    card->bingo = 0;

    return card;
}

void printCard(bingoCard *card) {
    // prints the bingo card
    printf(" B   I   N   G   O\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (card->card[i][j] == 0 || card->marked[i][j] == 1) {
                // Print marked numbers or free space
                printf(" *  ");
            } else {
                printf("%2d  ", card->card[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
