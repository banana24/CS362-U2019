#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkTribute(int currentPlayer, int nextPlayer, int tributeRevealedCards[], struct gameState *post, int handPos) {
   struct gameState pre;
   int i, treasure = 0, action = 0, victory = 0; 
   memcpy(&pre, post, sizeof(struct gameState));

   //Tribute(currentPlayer, nextPlayer, tributeRevealedCards, post, handPos);
     tributeEffect(post, currentPlayer, nextPlayer);
   treasure = 0;
   action = 0;
   victory = 0;

   for(i = 0; i<2; i++){ //loop to count cards 
      if(tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold){
	 treasure +=2; 
      }
      else if(tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){
	 victory +=2;
      }
      else{
	 action +=2;
      }
   }

   if ((pre.discardCount[nextPlayer] + pre.deckCount[nextPlayer]) <= 1){ //Check for condition where deck and discard together == 1
      if (pre.deckCount[nextPlayer] > 0){ //If deck count is equal to 1
	 if(pre.deckCount[nextPlayer]-1 != post->deckCount[nextPlayer]){ //Make sure deckcount is decreased
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 }
	 if(pre.deck[nextPlayer][pre.deckCount[nextPlayer]-1] != tributeRevealedCards[0]){ //Tribute = last card in deck
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 } 
      }
      else if (pre.discardCount[nextPlayer] > 0){ //If discard count is equal to 1
	 if(pre.discardCount[nextPlayer]-1 != post->discardCount[nextPlayer]){ //Make sure discard count is decreased
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 }
	 if(pre.discard[nextPlayer][pre.discardCount[nextPlayer]-1] != tributeRevealedCards[0]){ //Tribute = last card in discard pile 
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 }
      }
   }
   if(tributeRevealedCards[1] == -1){ //If we only have 1 card make sure we only get benefits for 1, there are no doubles
      if (tributeRevealedCards[0] == copper || tributeRevealedCards[0] == silver || tributeRevealedCards[0] == gold){//Treasure cards
	 if(pre.coins+2 != post->coins){
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 }
      }

      else if (tributeRevealedCards[0] == estate || tributeRevealedCards[0] == duchy || tributeRevealedCards[0] == province || tributeRevealedCards[0] == gardens || tributeRevealedCards[0] == great_hall){//Victory Card Found
	 if(pre.handCount[currentPlayer]+2 != post->handCount[currentPlayer]){
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 }
      }
      else{//Action Card
	 if(pre.numActions+2 != post->numActions){
	    printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
	 }
      }
   }
   else if (tributeRevealedCards[0] != -1 && tributeRevealedCards[1] != -1){ //Have two valid tribute cards
      if(pre.coins+treasure != post->coins){
	 printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
      }
      if(pre.handCount[currentPlayer]+victory != post->handCount[currentPlayer]){
	 printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
      }
      if(pre.numActions+action != post->numActions){
	 printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
      }
   }
   return 0;
}

int main () {

   int i, n, p, m, randSupply, nextPlayer, handPos, fixed, randTreasure;

   int k[10] = {adventurer, council_room, feast, gardens, mine,
      remodel, smithy, village, baron, great_hall};
   int tributeRevealedCards[2] = {-1,-1}; 

   struct gameState G;

   printf ("Testing Tribute.\n");

   printf ("RANDOM TESTS.\n");

   SelectStream(2);
   PutSeed(3);
   for (n = 0; n < 20000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
	 ((char*)&G)[i] = floor(Random() * 256);
      }
      //Set game state current player 
      p = floor(Random() * 3);
      fixed = floor(Random() * 21);
      randSupply = floor(Random() * 24); 
      randTreasure = 4 + floor(Random() * 3); 
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);
      G.playedCardCount = floor(Random() * 200);

      for( m = 0; m< G.playedCardCount; m++){ //Fill played cards with random supply cards
	 G.playedCards[m] = randSupply;
      }

      //Set game state next player
      nextPlayer = p+1;
      G.deckCount[nextPlayer] = floor(Random() * MAX_DECK);
      G.discardCount[nextPlayer] = floor(Random() * MAX_DECK);
      G.handCount[nextPlayer] = floor(Random() * MAX_HAND);

      for ( m=0; m<G.deckCount[nextPlayer]; m++){ //Fill next players deck with supply cards
	 G.deck[nextPlayer][m] = randSupply;
      } 

      for ( m = 0; m<G.discardCount[nextPlayer]; m++){ //Fill next players discard pile with supply cards
	 G.discard[nextPlayer][m] = randSupply;
      }

      if(fixed == 0 || fixed == 2 || fixed == 4 || fixed == 6){ //Don't need to randomize tribute because it gets replaced with first card in discard pile 
	 G.discardCount[nextPlayer] = 1;
	 G.deckCount[nextPlayer] = 0;
      }
      else if( fixed == 1 || fixed == 3 || fixed == 5 || fixed == 7){ //Don't need to randomize tribute because it gets replaced with first card in deck
	 G.discardCount[nextPlayer] = 0;
	 G.deckCount[nextPlayer] = 1;
      }
      else if ( fixed == 8 || fixed == 9 || fixed == 10 || fixed == 11){ //Chance to Force tributes to both be treasures
	 tributeRevealedCards[0] = randTreasure;
	 tributeRevealedCards[1] = randTreasure;
	 G.deckCount[nextPlayer] = 10;
      }
      else if (fixed == 12 || fixed == 13 || fixed == 14){ //Chance to force tributes to both be victory cards
	 tributeRevealedCards[0] = (randTreasure-3);
	 tributeRevealedCards[1] = (randTreasure-3);
	 G.deckCount[nextPlayer] = 0;
      }
      else if( fixed == 15 || fixed == 16 || fixed == 17){ //Randomize tributes
	 tributeRevealedCards[0] = randSupply;
	 tributeRevealedCards[1] = p + fixed;
      }

      checkTribute(p,nextPlayer,tributeRevealedCards, &G, handPos);
   }
   return 0;
}
