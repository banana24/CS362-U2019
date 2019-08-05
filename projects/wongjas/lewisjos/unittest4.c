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
   //printf("Assert failed\n"); 
   return 0;
}

int main() {
   int i,j;
   int num_Deck, num_Discard, num_Cards, num_Coins, num_actions, hold_Assert = 0;
   int total_Assert = 0;
   int currentPlayer = 1, nextPlayer = 2, handPos = 0;  
   int seed = 1000;
   int tributeRevealedCards[2] = {-1, -1}; 
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   initializeGame(numPlayer, k, seed, &state); // initialize a new game

   for( i = 0; i<2; i++){
      printf("Setting DISCARD count to: %d\n", i);
      for(j = 0; j<2; j++){ 
	 printf("Changing DECK count to: %d\n\n", j);
	 state.discardCount[nextPlayer] = i;
	 state.deckCount[nextPlayer] = j;
	 num_Deck = state.deckCount[nextPlayer];
	 num_Discard = state.discardCount[nextPlayer];

	 //Tribute(currentPlayer, nextPlayer, tributeRevealedCards, &state, handPos);
	 tributeEffect(&state, currentPlayer, nextPlayer);
	 if ( i == 1 && j == 1){
	    hold_Assert += assertTrue(-3, state.deckCount[nextPlayer]);
	    hold_Assert += assertTrue(1, state.discardCount[nextPlayer]);
	    total_Assert+=2;
	 }
	 else{

	    hold_Assert += assertTrue(0, state.deckCount[nextPlayer]);  
	    hold_Assert += assertTrue(0, state.discardCount[nextPlayer]);
	    total_Assert+=2;
	 }
	 printf("Deck count (nextPlayer) Before: %d, After: %d\n", num_Deck, state.deckCount[nextPlayer]);
	 printf("Discard count (nextPlayer) Before: %d, After: %d\n\n", num_Discard, state.discardCount[nextPlayer]);
      }
   }

   initializeGame(numPlayer, k, seed, &state); // initialize a new game

   for( i=0; i<4; i++){
      num_Coins = state.coins; 
      num_actions = state.numActions; 
      num_Cards = numHandCards(&state);
      tributeRevealedCards[0] = province+i;
      tributeRevealedCards[1] = province+i+i;
      tributeRevealedCards[2] = province+i+i+i;
     // Tribute(currentPlayer, nextPlayer, tributeRevealedCards, &state, handPos);
      tributeEffect(&state, currentPlayer, nextPlayer);

      printf("\nTribute function runs\n");
      hold_Assert += assertTrue(tributeRevealedCards[0], province+i);
      hold_Assert += assertTrue(tributeRevealedCards[1], province+i+i);
      hold_Assert += assertTrue(tributeRevealedCards[2], province+i+i+i);
      total_Assert+=3;
      printf("Tribute card index %d value: %d\n", 0, tributeRevealedCards[0]);
      printf("Tribute card index %d value: %d\n", 1, tributeRevealedCards[1]);
      printf("Tribute card index %d value: %d\n", 2, tributeRevealedCards[2]);
      if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold){//Treasure cards
	 hold_Assert += assertTrue(num_Coins+2, state.coins);
	 total_Assert++;
      }

      else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){//Victory Card Found
	 hold_Assert += assertTrue(num_Cards+2, numHandCards(&state));
	 total_Assert++;
      }
      else{//Action Card
	 hold_Assert += assertTrue(num_actions+2, state.numActions);
	 total_Assert++;
      }
      printf("Coins before: %d after: %d\n",num_Coins, state.coins);
      printf("Actions before: %d after: %d\n",num_actions, state.numActions);
      printf("Cards in hand before: %d after: %d\n",num_Cards, numHandCards(&state));
   }
   printf("\n");
   printf("Total assertion passed: %d / %d\n", hold_Assert, total_Assert);

} 

