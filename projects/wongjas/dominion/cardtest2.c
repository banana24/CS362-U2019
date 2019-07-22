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
   int i,m = 0;
   int seed = 2000;
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

   for(i=-1; i<1; i++){
      state.deckCount[numPlayer] = 0;
      m = shuffle(numPlayer,&state);
      printf("\nSetting deck number to be invalid value: %d\nNo assert failed statement is expected: \n\n", i); 
      assertTrue(m, -1);
   }

   for( numPlayer=0; numPlayer<4; numPlayer++){

      if(numPlayer == 3){
	numPlayer = 200;
      initializeGame(4, k, seed, &state); // initialize a new game
      printf("Increase deck count by after every player\n");
      printf("Current deck count: %d\n", (1+(numPlayer*2)));
      state.deckCount[3] = (1+(numPlayer*2));
      printf("Player: %d\n", 3);
      printf("Expect same type of card, in a different order\n");
      printf("Deck before: ");

      for( i= 0; i<state.deckCount[3]; i++){
	 printf("%d ", state.deck[3][i]);
      }
      printf("\n");
      printf("Deck after: ");
      m = shuffle(3, &state); 
      for( i= 0; i<state.deckCount[3]; i++){
	 // m = shuffle(numPlayer, &state); 
	 printf("%d ", state.deck[3][i]);
      }
      assertTrue((1+(numPlayer*2)), state.deckCount[3]);
      printf("\n\n");

      }

      else{
      initializeGame(4, k, seed, &state); // initialize a new game
      printf("Increase deck count by after every player\n");
      printf("Current deck count: %d\n", (1+(numPlayer*2)));
      state.deckCount[numPlayer] = (1+(numPlayer*2));
      printf("Player: %d\n", numPlayer);
      printf("Expect same type of card, in a different order\n");
      printf("Deck before: ");
      for( i= 0; i<state.deckCount[numPlayer]; i++){
	 printf("%d ", state.deck[numPlayer][i]);
      }
      printf("\n");
      printf("Deck after: ");
      m = shuffle(numPlayer, &state); 
      for( i= 0; i<state.deckCount[numPlayer]; i++){
	 // m = shuffle(numPlayer, &state); 
	 printf("%d ", state.deck[numPlayer][i]);
      }
      assertTrue((1+(numPlayer*2)), state.deckCount[numPlayer]);
      printf("\n\n");
      }

   }



}
