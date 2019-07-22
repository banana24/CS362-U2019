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
   int r,m = 0;
   int seed = 1000;
   int numPlayer;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   for(numPlayer = 1; numPlayer<6; numPlayer++){

      if(numPlayer == 2){
	 m++;
	 r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
	 state.numActions ++;
	 state.numBuys ++;
	 printf("\nPlayers: %d\n", numPlayer);
	 printf("Increased number of actions and buys expect: 2 for both. Buys: %d, Actions: %d\n", state.numBuys, state.numActions);

	 assertTrue(state.numBuys, 2);
	 assertTrue(state.numActions, 2);
	 printf("Hand size: %d, expect 5\n", numHandCards(&state));
	 assertTrue(numHandCards(&state), 5);

	 printf("Players: %d\n", numPlayer);
	 printf("Curse card supply count: %d, expected: %d\n", state.supplyCount[curse], 10*m);
	 assertTrue(state.supplyCount[curse], 10*m);
	 printf("Victory card count estate: %d, expected: %d\n", state.supplyCount[estate], 8);
	 assertTrue(state.supplyCount[estate],8); 
	 printf("Victory card count duchy: %d, expected: %d\n", state.supplyCount[duchy], 8);
	 assertTrue(state.supplyCount[duchy],8); 
	 printf("Victory card count province: %d, expected: %d\n", state.supplyCount[province],  8);
	 assertTrue(state.supplyCount[province],8);

	 printf("Copper count: %d, expected: %d\n", state.supplyCount[copper], 60 - (7 * numPlayer));
	 assertTrue(state.supplyCount[copper], 60 - ( 7 * numPlayer));
	 printf("Silver count: %d, expected: %d\n", state.supplyCount[silver],  40);
	 assertTrue(state.supplyCount[silver],40);
	 printf("gold count: %d, expected: %d\n\n", state.supplyCount[gold],  30);
	 assertTrue(state.supplyCount[gold],30);
      }

      else if(numPlayer>2 && numPlayer<5){
	 m++;
	 r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
	 printf("\nPlayers: %d\n", numPlayer);
	 printf("Number of actions and buys expect: 1 for both. Buys: %d, Actions: %d\n", state.numBuys, state.numActions);

	 assertTrue(state.numBuys, 1);
	 assertTrue(state.numActions, 1);
	 printf("Hand size: %d, expect 5\n", numHandCards(&state));
	 assertTrue(numHandCards(&state), 5);

	 printf("Curse card count: %d, expected: %d\n", state.supplyCount[curse],10*m);
	 assertTrue(state.supplyCount[curse], 10*m);
	 printf("Victory card count estate: %d, expected: %d\n", state.supplyCount[estate], 12);
	 assertTrue(state.supplyCount[estate],12); 
	 printf("Victory card count duchy: %d, expected: %d\n", state.supplyCount[duchy], 12);
	 assertTrue(state.supplyCount[duchy],12); 
	 printf("Victory card count province: %d, expected: %d\n", state.supplyCount[province], 12);
	 assertTrue(state.supplyCount[province],12);

	 printf("Copper count: %d, expected: %d\n", state.supplyCount[copper], 60 - (7 * numPlayer));
	 assertTrue(state.supplyCount[copper], 60 - ( 7 * numPlayer));
	 printf("Silver count: %d, expected: %d\n", state.supplyCount[silver],  40);
	 assertTrue(state.supplyCount[silver],40);
	 printf("gold count: %d, expected: %d\n\n", state.supplyCount[gold],  30);
	 assertTrue(state.supplyCount[gold],30);
      }
      else{

	 r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
	 printf("\nNumber of players: %d\nExpect nothing to happen and no assertion error if assert catches it\n", numPlayer);	
	 assertTrue(r, -1);
      }
   }
   k[1] = adventurer;
   r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
   printf("\nDuplicate kingdom card adventurer inserterted, expect no error message if assert catches it\n");
   assertTrue(r, -1);
   printf("\n");
}
