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
   int i;
   int seed = 2000;
   int numPlayer = 3, num_Hand, num_Discard;

   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   for( i = 0; i<6; i++){
      initializeGame(numPlayer, k, seed, &state); // initialize a new game
      num_Hand = numHandCards(&state);
      num_Discard = state.discardCount[state.whoseTurn];
      if(i==0){

	 printf("\nChange deck size to 1\n");
	 state.deckCount[state.whoseTurn] = 1;
	 assertTrue(state.deckCount[state.whoseTurn], 1);
      }
      else if(i==1){
	 printf("\nChange deck size to 10\n");
	 state.deckCount[state.whoseTurn] = 10;
	 assertTrue(state.deckCount[state.whoseTurn], 10);
      }

      else if(i==2){
	 printf("\nChange deck size to 500\n");
	 state.deckCount[state.whoseTurn] = 500;
	 assertTrue(state.deckCount[state.whoseTurn], 500);
      }
      else if(i==3){
	 printf("\nChange deck size to -30\n");
	 printf("Expect an increased of cards if discard count is greater than 0\n");
	 printf("Discard count: %d\n", num_Discard);
	 state.deckCount[state.whoseTurn] = -30;
	 assertTrue(state.deckCount[state.whoseTurn], -30);
      }

      else if(i==4){
	 printf("\nChange deck size to 0\n");
	 printf("Expect an increased of cards if discard count is greater than 0\n");
	 printf("Discard count: %d\n", num_Discard);
	 state.deckCount[state.whoseTurn] = 0;
	 assertTrue(state.deckCount[state.whoseTurn], 0);
	 assertTrue(state.discardCount[state.whoseTurn], 0);
      }
      else if(i==5){
	 printf("\nChange deck size to 0\n");
	 printf("Change discard size to 1\n");
	 printf("Expect an increased of cards if discard count is greater than 0\n");
	 state.deckCount[state.whoseTurn] = 0;
	 state.discardCount[state.whoseTurn] = 1;
	 assertTrue(state.deckCount[state.whoseTurn], 0);
	 printf("Discard count: %d\n", state.discardCount[state.whoseTurn]);
	 assertTrue(state.discardCount[state.whoseTurn], 1);
      }
      printf("Use drawCard function\n"); 
      drawCard(state.whoseTurn, &state);

      if(i==3 || i==4){
	 printf("Hand size before: %d, after: %d, expected: %d\n\n",num_Hand, numHandCards(&state), num_Hand);
	 assertTrue(numHandCards(&state), num_Hand);
      }
      else{
	 printf("Hand size before: %d, after: %d, expected: %d\n\n",num_Hand, numHandCards(&state), num_Hand+1);
	 assertTrue(numHandCards(&state), num_Hand+1);
      }
   }

}
