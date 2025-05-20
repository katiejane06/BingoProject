#include "projBingo.h"

int testRepeat(bingoCard card, int row, int col, int newNum) {
    //check if the number is already in the card
    for (int i = 0; i < ROWS; i++) {
        if(card[i][col] == newNum)
            return 1; // number already exists in the column
    }
    return 0; // number does not exist in the card
}

int randomNumer(int min, int max) {
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
        } while (testRepeat(*card, i, col, newNum));
        card->card[i][col] = newNum;
    }
}



void initializeCard(bingoCard *card) {
    // Initialize the card with random numbers column by column
    initializeColumn(card->card, 0, 1, 15);
    initializeColumn(card->card, 1, 16, 30);
    initializeColumn(card->card, 2, 31, 45);
    initializeColumn(card->card, 3, 46, 60);
    initializeColumn(card->card, 4, 61, 75);
    // Set the center space to 0 (free space)
    card[2][2] = 0;
}