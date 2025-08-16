#include "projBingoGame.h"
//want to make it so its vs a variable number of computers, generate a card for each computer and track when they get bingo

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
void callBall(bingoGame * game, bingoCard *card) {
    // Call a random ball number
    int ballNum;
    do {
        ballNum = randomNumber(1, BALLS);
    } while (game->balls[ballNum - 1] == 1); // Ensure the ball hasn't been called before
    game->balls[ballNum - 1] = 1; // Mark the ball as called
    game->numCalls++; // Increment the number of calls
    printCall(ballNum); // Print the called ball number
    autoDaubCheck(card, ballNum); // Check if the called ball is on the card
    printw("\n");
    refresh(); // Refresh the screen to show the printed call
}
    
void printCalls(bingoGame *game) {
    // Print the called balls
    printw("Called Balls: ");
    for (int i = 0; i < BALLS; i++) {
        if (game->balls[i] == 1) {
            printCall(i + 1); // Print the ball number
            printw(" (Hit key to daub space)\n");
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


int daubSpace(bingoCard *card, WINDOW *win) {
    int row, col;
    // player will input a letter and a number to daub a space
    clear(); // Clear the screen before prompting
    printCardNC(card, win); // Print the current card state
    refresh(); // Refresh to show the cleared screen
    printw("Enter Daub location (e.g., B3): ");
    echo(); // Enable echo to see input
    scanw(" %c%d", &col, &row);
    if(col == '0'){
        return 0;
    }
    noecho(); // Disable echo after input
    int colEnum = get_column_enum(col);
    if (colEnum == -1 || row < 1 || row > ROWS) {
        printw("Invalid input. Please enter a valid column letter (B, I, N, G, O) and a number between 1 and %d.\n", COLS);
        getch(); // Wait for user to read the message
        return -1; // Invalid input
    }
    col = colEnum; // Convert to zero-based index
    row = row - 1; // Convert to zero-based index
    markSpace(card, row, col); // Mark the space on the card
    printCardNC(card, win); // Print the card to show the marked space
    return 0; // Successfully daubed the space
}

int gamePlay() {
    // Main game loop
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input characters
    refresh();
    getch();
        WINDOW * card_win = newwin(8, 23, 4, 0); // Create a new window for the card
        bingoCard * playerCard = createCard(); // Create a new bingo card
        printCardNC(playerCard, card_win); // Print the bingo card in the window
        wrefresh(card_win); // Refresh the window to show the card
        bingoGame * game = createGame(); // Create a new bingo game
        getch();
        while(game->numCalls < BALLS) {
            werase(stdscr); // Clear the main screen
            wrefresh(stdscr); // Refresh to show the cleared screen
            printCardNC(playerCard, card_win); // Print the bingo card in the window
            callBall(game, playerCard); // Call a ball
            timeout(8000); // Set a timeout of 8 seconds for user input
            int ch = getch(); // Wait for user input
            timeout(-1);
            if (ch != ERR){
                // User input detected, daub a space
                while(daubSpace(playerCard, card_win) == -1); // Prompt the user to daub a space until valid input is given
            }

            if(bingoCheck(playerCard->expectedMarked) && bingoCheck(playerCard->card)) {
                printw("Bingo! You won!\n");
                break;
            }
        }

    getch(); // Wait for user input to continue
    endwin();
    return 0; // Game continues
}