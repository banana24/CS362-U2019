#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkMinion(int choice1, int choice2, struct gameState *post, int  handPos, int player) {
   struct gameState pre; 
   int i,j, count = 0;
   memcpy(&pre, post, sizeof(struct gameState)); //Make a copy of the previous struct

//   Minion(choice1, choice2, post, handPos, player);
      minionEffect(post, player, handPos, choice1, choice2);

   if(pre.numActions+1 != post->numActions){ //The players number of actions should always increase check for an increase
      printf("Error at line %d in function \"%s\" values of pre/post Actions not expected\n",((__LINE__)-1),__func__);
   }

   if(choice1){
      if(pre.coins+2 != post->coins){ //Check for an increase in coins
	 printf("Error at line %d in function \"%s\" values not expected\n",((__LINE__)-1),__func__);
      }
      if(pre.numBuys != post->numBuys || pre.coins != post->coins){ //Check if coins or buys increase, it shouldn't 
	 printf("Error at line %d in function \"%s\" values of pre/post coins or buys not expected\n",((__LINE__)-1),__func__);
      }
   }

   else if(choice2){ //Discard hand for current player and gain 4 cards, all other players with over 4 cards discard their hand and redraw
      if(post->handCount[player] != 4){ //First check if the player discarded their hand by verifying they now have 4 cards
	 count = 0;
	 for(i=0; i<4; i++){//Next make sure that the hands before and after are different for the first 4 cards
	    if(pre.hand[player][i] == post->hand[player][i]){
	       count++;
	    }
	    if(count == 4){
	       printf("Error at line %d in function \"%s\" cards not discarded not expected\n",((__LINE__)-1),__func__);

	    }
	 }

	 for (i = 0; i < pre.numPlayers; i++) //For all the other players 
	 {
	    if (i != player)
	    {
	       if ( pre.handCount[i] > 4 ){ //Tests if the player has more than 4 cards
		  count = 0;
		  for(j=0; j<4; j++){//Check the hands before and after are different for the first 4 cards
		     if(pre.hand[player][j] == post->hand[player][j]){
			count++;
		     }
		     if(count == 4){
			printf("Error at line %d in function \"%s\" players hand was not discarded\n",((__LINE__)-1),__func__);
		     }
		  }
	       }

	       else{ //If they don't have 4 or more cards check if their discard pile changed to verify they didn't discard their hand
		  for (i = 0; i < pre.numPlayers; i++)
		  {
		     if ( pre.discardCount[i] != post->discardCount[i] ){ //Altered code to cause incorrect behavior
			printf("Error at line %d in function \"%s\" other players hand was discarded, it shouldn't\n",((__LINE__)-1),__func__);

		     }
		  }
	       }
	    }
	 }
      }
   }
   return 0;
}

int main () {

   int i, n,m,  p, choice1, choice2, handPos, hold_hand, hold_choice2;

   int k[10] = {adventurer, council_room, feast, gardens, mine,
      remodel, smithy, village, baron, great_hall};

   struct gameState G;

   printf ("Testing drawCard.\n");

   printf ("RANDOM TESTS.\n");

   SelectStream(2);
   PutSeed(3);

   for (n = 0; n < 2; n++) {
      //initializeGame(p, k, 1, &G);
      for (i = 0; i < sizeof(struct gameState); i++) {
	 ((char*)&G)[i] = floor(Random() * 256);
      }
      p = floor(Random() * 4);
      //memset(&G, 23, sizeof(struct gameState));
      //initializeGame(p, k, 1, &G);
      choice1 = floor(Random() * 2);
      //initializeGame(p, k, 1, &G);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);
      G.whoseTurn = p; 
      hold_hand = G.handCount[p];
      G.playedCardCount = floor(Random()*200);
      handPos = floor(Random() * G.handCount[p]);



      for( m = 0; m < G.playedCardCount; m++){ //Filled played card count with random supply 
	 G.playedCards[m] = floor(Random() * 24);
      }

      for (m = 0; m < G.handCount[p]; m++){ //Fill hand count with random supply 
	 G.hand[p][m] = floor(Random() * 24);
      }
      for ( m = 0; m < G.deckCount[p]; m++){ //Fill deck count with random supply
	 G.deck[p][m] = floor(Random() * 24);
      }
      for (m = 0; m < G.discardCount[p]; m++){ //Fill discard count with random supply
	 G.discard[p][m] = floor(Random() * 24);
      }

      if (choice1 == 1){ //Setting choices
	 choice2 = 0;
      }
      else if (choice1 == 0){
	 choice2 = 1;
      }	 

//      checkMinion(choice1, choice2, &G, handPos, p);
      minionEffect(&G, p, handPos, choice1, choice2);
      //choice2 = 1;
      //Print statements I used to verify values
      /* 
	 printf("Printing p: %d\n", p);
	 printf("Printing choice1: %d\n", choice1);
	 printf("Printing choice2: %d\n", choice2);
	 printf("Printing hold_choice2: %d\n", hold_choice2);
	 printf("Printing deckCount: %d\n", G.deckCount[p]);
	 printf("Printing discardCount: %d\n", G.discardCount[p]);

	 printf("Printing handCount: %d\n", G.handCount[p]);
	 printf("Printing hold_hand: %d\n", hold_hand);
	 printf("Printing handPos: %d\n", handPos);
	 printf("Printing whoseTurn: %d\n", G.whoseTurn);
	*/ 
      //checkMinion(choice1, choice2, &G, handPos, p);
   }
   return 0;
}
