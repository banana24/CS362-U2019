/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
   int choice, currentPlayer, num_Cards, num_Coins, num_Discard, num_state;
   int seed = 1000;
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   initializeGame(numPlayer, k, seed, &state); // initialize a new game


   printf("First player\n");	
   currentPlayer = 0; //First player
   choice = 1; //First choice, discard an estate to gain coins
   num_Cards =  numHandCards(&state);
   assert( numHandCards(&state) == 5); 	
   num_Discard = state.discardCount[currentPlayer]; 	
   assert(state.discardCount[currentPlayer] == 0); 	
   //Baron(choice, &state, currentPlayer);
   baronEffect(&state, currentPlayer, choice);
   assert(state.numBuys == 2);
   printf("This is the number of buys the first player has: %d, expected 2 \n", state.numBuys);
   assert(state.coins == 8); 
   printf("Should have 8 coins, value: %d\n", state.coins); 
   assert(numHandCards(&state) == 4);
   printf("Cards After Baron used: %d, Before Baron is used: %d\n", numHandCards(&state), num_Cards);
   printf("Cards in discard count after Baron function used: %d, Before Baron is used: %d\n", state.discardCount[currentPlayer], num_Discard); 	
      
   endTurn(&state);	
   printf("\n\n");

   printf("Second player\n");	
   currentPlayer = 1; //Second player
   choice = 0; //Second choice, gain an estate 
   state.numBuys--; //Decrease the number of buys 
   num_Coins = state.coins; 
   num_Cards = numHandCards(&state);
   num_Discard = state.discardCount[currentPlayer];
   num_state = state.supplyCount[estate];
   //Baron(choice, &state, currentPlayer);
   baronEffect(&state, currentPlayer, choice);
   assert(state.numBuys == 1); 
   printf("Number of buys the second player has: %d, expected 1 \n", state.numBuys);
   assert(state.coins == 3);
   printf("Coins I had before: %d, Coins I have afterwards: %d\n\n", num_Coins, state.coins); 
   assert(num_Cards == 5);
   printf("Cards before Baron function used (gain estate): %d, after Baron is used: %d\n ", num_Cards, numHandCards(&state));
   assert(state.numBuys == 1); 
   assert(state.discardCount[currentPlayer] == 1);
   printf("Discard count before Baron function used: %d, after Baron is used: %d\n", num_Discard, state.discardCount[currentPlayer]); 	
   printf("Estate cards Before: %d, After: %d\n", num_state, state.supplyCount[estate]);	
   endTurn(&state);

   memset(&state, 23, sizeof(struct gameState));
   initializeGame(numPlayer, k, seed, &state); // initialize a new game
   state.supplyCount[estate] = 0;
   state.supplyCount[smithy] = 0; 
   state.supplyCount[village] = 0;
   assert(isGameOver(&state) == 1); //isGameOver returns 1 if the game has ended
   printf("Game sucessfully ended\n\n");  

   return 0;
}

