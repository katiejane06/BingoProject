#include "projBingoGame.h"

bingoGame *createGame() {
    // Allocate memory for a new bingo game
    bingoGame *game = (bingoGame *)malloc(sizeof(bingoGame));
    if (game == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Initialize the ball list with 0s
    for (int i = 0; i < BALLS; i++) {
        game->balls[i] = i+1; // Fill with numbers 1 to 74
    }
    game->numCalls = 0; // Initialize the number of calls to 0
    return game;
}

void printCall(int ballNum)
{
    // Print the called ball number
    if (ballNum < 1 || ballNum > BALLS) {
        printf("Invalid ball number: %d\n", ballNum);
        return;
    }
    if(ballNum > 60){
        printf("O%d", ballNum);
    }
    else if(ballNum > 45){
        printf("G%d", ballNum);
    }
    else if(ballNum > 30){
        printf("N%d", ballNum);
    }
    else if(ballNum > 15){
        printf("I%d", ballNum);
    }
    else{
        printf("B%d", ballNum);
    }
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
    printf("\n");
}
    
void printCalls(bingoGame *game) {
    // Print the called balls
    printf("Called Balls: ");
    for (int i = 0; i < BALLS; i++) {
        if (game->balls[i] == 1) {
            printCall(i + 1); // Print the ball number
            printf(" ");
        }
    }
    printf("\n");
}