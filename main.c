//Katherine Lawler
//Bingo Card Header File
//Description: This file contains the main function for the bingo game.

#include "projBingo.c"
#include "projBingoGame.c"


int main(void){
    srand(time(NULL)); // Seed the random number generator
    bingoCard * card = createCard();
    printCard(card);
    return 0;
}