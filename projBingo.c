#include "projBingo.h"

int testRepeat(int card[ROWS][COLS], int row, int col, int newNum) {
    //check if the number is already in the card
    for (int i = 0; i < ROWS; i++) {
        if(card[i][col] == newNum)
            return 1; // number already exists in the column
    }
    return 0; // number does not exist in the card
}

int randomNumber(int min, int max) {
    // Generate a random number between min and max
    return (rand() % (max - min + 1)) + min;
}

void initializeColumn(int card [ROWS][COLS], int col, int min, int max) {
    // Initialize a column with random numbers between min and max
    for (int i = 0; i < ROWS; i++) {
        int newNum;
        do {
            newNum = randomNumber(min, max);
        } while (testRepeat(card, i, col, newNum));
        card[i][col] = newNum;
    }
}

void initializeCard(int card [ROWS][COLS]) {
    // Initialize the card with random numbers column by column
    initializeColumn(card, 0, 1, 15);
    initializeColumn(card, 1, 16, 30);
    initializeColumn(card, 2, 31, 45);
    initializeColumn(card, 3, 46, 60);
    initializeColumn(card, 4, 61, 75);
    // Set the center space to 0 (free space)
    card[2][2] = 0;
}

bingoCard *createCard() {
    // Allocate memory for a new bingo card
    bingoCard *userCard = (bingoCard *)malloc(sizeof(bingoCard));
    if (userCard == NULL) {
        printw("Memory allocation failed\n");
        return NULL;
    }
    // Initialize the card
    initializeCard(userCard->card);
    // Initialize the marked arrays
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            userCard->marked[i][j] = 0;
            userCard->expectedMarked[i][j] = 0; // Mark all spaces as unmarked
        }
    }
    userCard->marked[2][2] = 1; // Mark the free space
    userCard->expectedMarked[2][2] = 1; // Mark the free space as expected
    // Initialize other fields
    userCard->numMarked = 1;
    userCard->expectedNumMarked = 1;
    userCard->bingo = 0;

    return userCard;
}

computerCard *createComputerCard() {
    // Allocate memory for a new computer bingo card
    computerCard *compCard = (computerCard *)malloc(sizeof(computerCard));
    if (compCard == NULL) {
        printw("Memory allocation failed\n");
        return NULL;
    }
    // Initialize the card
    initializeCard(compCard->card);
    // Initialize other fields
    compCard->expectedNumMarked = 0;
    compCard->bingo = 0;

    return compCard;
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
    if (card->marked[row][col] == 1) {
        printw("Space already marked\n");
        return;
    }
    card->marked[row][col] = 1; // Mark the space
    card->numMarked++; // Increment the number of marked spaces
}

void autoDaubCheck(bingoCard *card, int ballNum) {
    // Check if the called ball number is on the card and mark it in expectedMarked
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (card->card[i][j] == ballNum) {
                card->expectedMarked[i][j] = 1;
                card->expectedNumMarked++; // Increment the expected number of marked spaces
            }
        }
    }
}

int bingoCheck(int card[ROWS][COLS]) {
    // Check for bingo in rows, columns, and diagonals
    for (int i = 0; i < ROWS; i++) {
        int rowBingo = 1;
        int colBingo = 1;
        for (int j = 0; j < COLS; j++) {
            if (card[i][j] == 0) {
                rowBingo = 0; // Row not complete
            }
            if (card[j][i] == 0) {
                colBingo = 0; // Column not complete
            }
        }
        if (rowBingo || colBingo) {
            return 1; // Bingo found
        }
    }
    // Check diagonals
    int diag1Bingo = 1;
    int diag2Bingo = 1;
    for (int i = 0; i < ROWS; i++) {
        if (card[i][i] == 0) {
            diag1Bingo = 0; // Diagonal 1 not complete
        }
        if (card[i][ROWS - 1 - i] == 0) {
            diag2Bingo = 0; // Diagonal 2 not complete
        }
    }
    if (diag1Bingo || diag2Bingo) {
        return 1; // Bingo found
    }
    return 0; // No bingo found
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

