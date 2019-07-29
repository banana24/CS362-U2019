#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


#define DEBUG 0
#define NOISY_TEST 1

int assertTrue(int compare1, int compare2){
   int number = 1;
   if ( compare1 == compare2 ){
      return number; 
   }
   else{
      printf("Assert failed\n");
      return 0;
   }
}

int checkBaron(int choice1, struct gameState *post, int player) {
   struct gameState pre; 
   memcpy(&pre, post, sizeof(struct gameState));
   int j, estate_flag;
   Baron(choice1, post, player);   

   if(choice1 > 0){ //Player chose to discard estate for +4, estate 
      estate_flag = 0;
      for (j=0; j< pre.handCount[player]; j++){ //Check for estate cards in hand
	 if(pre.hand[player][j] == estate){
	    estate_flag = 1;
	 }
      }
      if(estate_flag == 1){ //If players have an estate in their hand 
	 pre.coins += 4;

	 assertTrue(pre.coins, post->coins);
	 if(assertTrue(pre.discardCount[player], post->discardCount[player]-1) == 0){ //Check for correct discard pile changes
	    printf("Discard pile error for choice1 > 0, pre and post count do not match expected values \n");
	 }
	 if(post->discard[player][post->discardCount[player]-1] != 1){ //Test if estate was discarded
	    printf("Discard pile last card is not an estate, choice1 > 0");
	 }
	 if(assertTrue(pre.handCount[player], post->handCount[player]) == 0){ //Test if the hand was changed
	    printf("Hand count error for choice1 > 0, pre and post count do not match expected values, %d, %d\n", pre.handCount[player], post->handCount[player]); 
	 }

      }
      else{ //If players don't have an estate in their hands
	 if(assertTrue(pre.handCount[player], post->handCount[player]) == 0 && pre.supplyCount[estate] != 0){
	    printf("Hand count error for choice1 > 0, pre and post count do not match expected values, %d, %d\n", pre.handCount[player], post->handCount[player]); 
	 }
	 if(assertTrue(pre.supplyCount[estate], post->supplyCount[estate]+1) == 0 && pre.supplyCount[estate] != 0 ){
	    printf("Estate Count error for choice1 > 0, pre and post count do not match expected values\n");
	 }
      }
   }
   //Choice == 0
   else{
      if(assertTrue(pre.handCount[player], post->handCount[player]) == 0 ){ //Test if the hand count was changed
	 printf("Hand count error for choice1 == 0, pre and post count do not match expected values\n"); 
      }
      if(assertTrue(pre.supplyCount[estate]-1, post->supplyCount[estate]) == 0){ //Test if supply count for estate was changed
	 printf("Estate Count error for choice1 == 0, pre and post count do not match expected values\n");
      }
   }
   return 0;
}

int main () {

   int i, j, n,m, p, q, choice1, ranEstate;

   int k[10] = {adventurer, council_room, feast, gardens, mine,
      remodel, smithy, village, baron, great_hall};

   struct gameState G;

   printf ("Testing Baron.\n");

   printf ("RANDOM TESTS.\n");

   SelectStream(2);
   PutSeed(3);

   for (n = 0; n < 20000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
	 ((char*)&G)[i] = floor(Random() * 256);
      }
      //Initialize parts of the game state that is needed
      p = floor(Random() * 4);
      choice1 = floor(Random() * 2);
      G.coins = floor(Random() * 100);
      ranEstate = floor(Random() * 24);
      q = floor(Random() * 5);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);

      for(m = 0; m < G.discardCount[p]; m++){ //Fill discard pile with random supply 
	 G.discard[p][G.discardCount[p]] = floor(Random() * 24);
      }

      for(m = 0; m < G.handCount[p]; m++){ //Fill hand with random supply 
	 G.hand[p][G.handCount[p]] = floor(Random() * 24);
      }

      if( ranEstate == 2 || ranEstate == 4 || ranEstate == 8 || ranEstate == 10 || ranEstate == 12){
	 for (j=0; j< G.handCount[p]; j++){
	    G.hand[p][j] = estate; //Fill hand with estates randomly
	 }
      }

      else{
	 G.supplyCount[estate] = q; //Fill estate supply count randomly to randomly trigger end game
      }

      checkBaron(choice1, &G, p); 
   }

   return 0;
}
