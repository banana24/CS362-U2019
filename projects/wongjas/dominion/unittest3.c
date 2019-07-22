#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

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
   int num_Supply, num_Cards, hold_Return, hold_Assert;
   int choice1, choice2, total_Assert = 0;
   int currentPlayer = 0, handPos = 0;  
   int seed = 1000;
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   initializeGame(numPlayer, k, seed, &state); // initialize a new game

   num_Cards = numHandCards(&state); 
   num_Supply = state.supplyCount[copper];
   for( currentPlayer = 0; currentPlayer < 2; currentPlayer++){
      printf("Player: %d\n ", currentPlayer);

      for( i=-1; i<num_Cards; i++){
	 choice1 = 2;
	 choice2 = i;

	 hold_Return = Ambassador(choice1, choice2, &state, handPos, currentPlayer);
	 printf("%d: ", choice2); 
	 hold_Assert += assertTrue(0, hold_Return); //hold_Return returns 0 (pass) or -1 (fail) 
	 total_Assert++;
      }
      printf("Card in players hand: %d, expected 4\n", num_Cards);
      assertTrue(num_Cards, 4);
      total_Assert++; 
      printf("Player %d's hand count: %d\n", currentPlayer+1, state.handCount[2]);
      endTurn(&state);
   }

   currentPlayer =0;
   printf("\nTotal assertions passed (choices): %d / %d\n\n", hold_Assert, total_Assert);
   printf("Supply Count (estate) Before: %d, Afer: %d\n", num_Supply, state.supplyCount[state.hand[currentPlayer][choice1]]); 
   assertTrue(num_Supply, state.supplyCount[state.hand[currentPlayer][choice1]]-2);
   total_Assert++;
   printf("\n");

   currentPlayer = 1;
   printf("Player 1 hand: \n");
   for ( i=0; i<7; i++){
      //printf("Hand Before function is used\n");
      printf("Card #: %d\n", handCard(i, &state));
   }

   printf("Player 1 expected 6th card is enum 1(Estate), Actual: %d\n", handCard(5,&state));
   assertTrue(1, handCard(5, &state));
   total_Assert++;
   printf("\nTotal assertions passed: %d / %d\n\n", hold_Assert, total_Assert);

}





