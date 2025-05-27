//Katherine Lawler
//Bingo Card Header File
//Description: This file contains the main function for the bingo game.

#include "projBingo.h"
#include "projBingoGame.h"

int main(void){
    srand(time(NULL)); // Seed the random number generator
    gamePlay(); // Start the bingo game
    
    return 0;
}