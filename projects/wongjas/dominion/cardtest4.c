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
   int i,j, m;
   int seed = 2000;
   int numPlayer = 4;
   int players[MAX_PLAYERS];
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   for(m=0; m<2; m++){
      initializeGame(numPlayer, k, seed, &state); // initialize a new game
      if(m==0){

	 printf("\nPlayer 0 curse card for negative score\n");
	 printf("Player 1 hand with highest score gain province\n");
	 printf("Player 2 fill hand with non-treasure cards\n");
	 printf("Player 4 duplicate full province hand to test for ties\n\n");

      }
      else if(m==1){

	 printf("\nPlayer 0 curse card for negative score\n");
	 printf("Player 1 curse card for negative score\n");
	 printf("Player 2 full non-treasure hand for 0 score\n");
	 printf("Player 3 Set an invalid card\n");

      }

      for(j=0; j<4; j++){

	 printf("Players turn: %d\n", state.whoseTurn);
	 printf("Hand: ");

	 for( i= 0; i<5; i++){
	    if(j==0){
	       state.hand[state.whoseTurn][i] = curse;
	       printf("%d ", state.hand[state.whoseTurn][i]);
	    }
	    else if(j==1){
	       state.hand[state.whoseTurn][i] = (province - (m*3));
	       printf("%d ", state.hand[state.whoseTurn][i]);
	    }

	    else if(j==2){
	       state.hand[state.whoseTurn][i] = (adventurer);
	       printf("%d ", state.hand[state.whoseTurn][i]);
	    }
	    else{
	       state.hand[state.whoseTurn][i] = (province - (m*5));
	       printf("%d ", state.hand[state.whoseTurn][i]);
	    }
	 }
	 endTurn(&state);
	 printf("\n\n");
      }
      if(m==0){
	 getWinners(players, &state); 
	 for(i=0; i<state.numPlayers; i++){
	    printf("Player: %d, Placement: %d\n", i, players[i]);
	 }
	 printf("Expect 2 winners, player 0 & 1\n");
	 assertTrue(1, players[0]);
	 assertTrue(1, players[1]);

      }
      else{

	 getWinners(players, &state); 
	 for(i=0; i<state.numPlayers; i++){
	    printf("Player: %d, Placement: %d\n", i, players[i]);
	 }
	 printf("Expect 1 winner, player 3\n");
	 assertTrue(1, players[2]);
      }
   }
}
