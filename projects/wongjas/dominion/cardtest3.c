#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int assertTrue(int compare1, int compare2){
   int number = 1;
   if ( compare1 == compare2 ){
      return number; 
   }
   printf("Assert failed\n"); 
   return 0;
}

int main() {
   int i,j;
   int seed = 2000;
   int numCoins =0;
   int numPlayer = 3;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   initializeGame(numPlayer, k, seed, &state); // initialize a new game
   for(j=0; j<3; j++){
   printf("Whose turn is it? Player: %d\n", state.whoseTurn);

   if(j==0){

   printf("Boundary test attempt to increase actions, decrease buys, and multiply coins by 300\n");
   state.coins += 300;
   state.numActions -= 300;
   state.numBuys *= 300;
   printf("End Turn\n");
   endTurn(&state); 

   state.whoseTurn = 0;
   printf("Set the turn back to the previous player\n");
   printf("Whose turn is it? Player: %d\n", state.whoseTurn);
   printf("Check the previous players game state after ending their turn\n");
   printf("Ignore assertion failure for expected coins, it's an error because the endTurn function updates coins, it should be 4\n");
   }
   printf("Hand: ");

   numCoins = 0;
   for( i= 0; i<5; i++){
      if (state.hand[state.whoseTurn][i] == copper)
      {
	 numCoins++;
      }
      printf("%d ", state.hand[state.whoseTurn][i]);
   }

   printf("\n");
   printf("Phase: %d, Expected: 0\n", state.phase);
   assertTrue(0, state.phase);
   printf("Actions: %d, Expected: 1\n",state.numActions);
   assertTrue(1, state.numActions);
   printf("Buys: %d, Expected: 1\n", state.numBuys);
   assertTrue(1, state.numBuys);
   printf("Coins (based on treasure cards in hand): %d, Expected: %d\n",state.coins, numCoins);
   assertTrue(state.coins, numCoins);
   printf("Played Cards: %d, Expected: 0\n", state.playedCardCount);
   assertTrue(0, state.playedCardCount);
   printf("Hand Count: %d, Expected: %d \n", state.handCount[state.whoseTurn], state.handCount[state.whoseTurn]);
   assertTrue(state.handCount[state.whoseTurn], state.handCount[state.whoseTurn]);
   printf("Outpost played: %d, Expected: 0\n\n", state.outpostPlayed);
   assertTrue(0, state.outpostPlayed);
   endTurn(&state);
   }
}
