#include "projBingoGame.h"

bingoGame *createGame() {
    // Allocate memory for a new bingo game
    bingoGame *game = (bingoGame *)malloc(sizeof(bingoGame));
    if (game == NULL) {
        printw("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < BALLS; i++) {
        game->balls[i] = i+1; // Fill with numbers 1 to 74
    }
    game->numCalls = 0; // Initialize the number of calls to 0
    return game;
}

void printCall(int ballNum)
{
    clrtoeol(); // clear the line before printing the call
    // Print the called ball number
    if (ballNum < 1 || ballNum > BALLS) {
        printw("Invalid ball number: %d\n", ballNum);
        return;
    }
    if(ballNum > 60){
        printw("O%d", ballNum);
    }
    else if(ballNum > 45){
        printw("G%d", ballNum);
    }
    else if(ballNum > 30){
        printw("N%d", ballNum);
    }
    else if(ballNum > 15){
        printw("I%d", ballNum);
    }
    else{
        printw("B%d", ballNum);
    }
    refresh(); // Refresh the screen to show the printed call
    // Note: The mvprintw function is used for ncurses to print at specific coordinates
}
void callBall(bingoGame * game) {
    // Call a random ball number
    int ballNum;
    do {
        ballNum = randomNumber(1, BALLS);
    } while (game->balls[ballNum - 1] == 1); // Ensure the ball hasn't been called before
    game->balls[ballNum - 1] = 1; // Mark the ball as called
    game->numCalls++; // Increment the number of calls
    printCall(ballNum); // Print the called ball number
    printw("\n");
    refresh(); // Refresh the screen to show the printed call
}
    
void printCalls(bingoGame *game) {
    // Print the called balls
    printw("Called Balls: ");
    for (int i = 0; i < BALLS; i++) {
        if (game->balls[i] == 1) {
            printCall(i + 1); // Print the ball number
            printw(" ");
        }
    }
    printw("\n");
}

int get_column_enum(char c) {
    switch (toupper(c)) {
        case 'B': return B;
        case 'I': return I;
        case 'N': return N;
        case 'G': return G;
        case 'O': return O;
        default: return -1;  // invalid input
    }
}


int daubSpace(bingoCard *card) {
    int row, col;
    // player will input a letter and a number to daub a space
    printw("Enter Daub locatio : ");
    scanw("%c%d", &row, &col);
    int colEnum = get_column_enum(row);
    if (colEnum == -1 || col < 1 || col > COLS) {
        printw("Invalid input. Please enter a valid column letter (B, I, N, G, O) and a number between 1 and %d.\n", COLS);
        return -1; // Invalid input
    }
}

int gamePlay() {
    // Main game loop
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input characters
    refresh();
    getch();
    while (1) {
        WINDOW * card_win = newwin(8, 23, 4, 0); // Create a new window for the card
        bingoCard * playerCard = createCard(); // Create a new bingo card
        printCardNC(playerCard, card_win); // Print the bingo card in the window
        wrefresh(card_win); // Refresh the window to show the card
        bingoGame * game = createGame(); // Create a new bingo game
        getch();

        callBall(game); // Call a ball

       getch(); // Wait for user input to continue
       endwin();
       return 0; // For now, just return 1 to indicate the game continues
    }
    return 0; // Game continues
}