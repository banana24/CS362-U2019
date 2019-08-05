#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
   int i;
   int  num_Cards, num_Coins, num_actions;
   int choice1, choice2;
   int currentPlayer = 0, handPos = 0;  
   int seed = 1000;
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   initializeGame(numPlayer, k, seed, &state); // initialize a new game
	
   choice1 = 1; 
   choice2 = 0;

   for( i = 0; i<2; i++){
      num_Cards = numHandCards(&state); 
      num_actions = state.numActions; 
      num_Coins = state.coins; 
      minionEffect(&state, currentPlayer, handPos, choice1, choice2);
      assert( numHandCards(&state) == 4);
      printf("Current Player: %d\n", currentPlayer); 
      printf("Number of cards Before: %d, After: %d, Expected: 4 \n", num_Cards, numHandCards(&state));
      printf("Number of actions Before: %d, After: %d, Expected: 2 \n", num_actions, state.numActions);
      printf("Number of coins Before: %d, After: %d, Expected: 6 \n\n", num_Coins, state.coins);
      endTurn(&state);
      currentPlayer++; 
      state.coins = 4; //Reset coins for endTurn;
   }


   choice1 = 0; //Change the choices
   choice2 = 1; 
   state.coins = 4; // Reset coins to 4  
   currentPlayer = 0;
   memset(&state, 23, sizeof(struct gameState)); 
   initializeGame(3, k, seed, &state); // initialize a new game

   printf("Changed choices (Discard cards)\n");

   for( i = 0; i<2; i++){
      num_Cards = numHandCards(&state); 
      num_Coins = state.coins;

      minionEffect(&state, currentPlayer, handPos, choice1, choice2);
      printf("Current Player: %d\n", currentPlayer);
      if( num_Cards == 5 ){ 
	 assert(num_Cards-1 == numHandCards(&state));
	 assert( num_Coins == state.coins); 
	 printf("number of cards %d, expected: 4 \n", numHandCards(&state));
	 printf("Coins Before: %d, Coins After: %d, should be the same value \n\n", num_Coins, state.coins);
      }
      else if ( numHandCards(&state) < 5){
	 assert( num_Coins == state.coins); 
	 printf("Shouldn't have 4 cards, shouldn't be able to discard and redraw\n"); 
	 printf("number of cards before: %d, after: %d, expected: %d \n\n", num_Cards, numHandCards(&state), num_Cards);
	 printf("Coins Before: %d, Coins After: %d, should be the same value \n\n", num_Coins, state.coins); 

      }

      endTurn(&state);
      currentPlayer++;
      discardCard(2, currentPlayer, &state, 1);
      discardCard(3, currentPlayer, &state, 1);

   }

}

