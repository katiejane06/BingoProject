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
        printw("Memory allocation failed\n");
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
                printw(" *  ");
            } else {
                printw("%2d  ", card->card[i][j]);
            }
        }
        printw("\n");
    }
    printw("\n");
}

void markSpace(bingoCard *card, int row, int col) {
    // Mark a space on the card
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printw("Invalid row or column index\n");
        return;
    }
    if (card->marked[row][col] == 1) {
        printw("Space already marked\n");
        return;
    }
    card->marked[row][col] = 1; // Mark the space
    card->numMarked++; // Increment the number of marked spaces
}

void printCardNC(bingoCard *card, WINDOW *win) {
    // Print the bingo card using ncurses
    if(win == NULL) {
        printw("Window is NULL\n");
        return;
    }
    werase(win);
    box(win, 0, 0); // Draw a box around the window
    mvwprintw(win, 1, 2, " B   I   N   G   O");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (card->card[i][j] == 0 || card->marked[i][j] == 1) {
                // Print marked numbers or free space
                mvwprintw(win, i + 2, (j * 4)+2, " *  ");
            } else {
                mvwprintw(win, i + 2, (j * 4)+2, "%2d  ", card->card[i][j]);
            }
        }
    }
    move(0,0);
    wrefresh(win);
}

