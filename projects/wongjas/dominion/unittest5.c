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
   int i,j,m,r;
   int choice1, choice2;
   int currentPlayer = 0, handPos = 0;  
   int seed = 1000;
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
      , remodel, smithy, village, baron, great_hall};
   struct gameState state;

   for ( i=0; i<5; i++){
      choice1 = 6;

      initializeGame(numPlayer, k, seed, &state); // initialize a new game

      gainCard(copper, &state, 2, currentPlayer);
      gainCard(silver, &state, 2, currentPlayer);
      gainCard(gold, &state, 2, currentPlayer);
      gainCard(gardens, &state, 2, currentPlayer);

      printf("Cards in hand: ");

      for( m=0; m<9; m++){
	 printf(" %d", handCard(m, &state)); 
      }

      printf("\n");
      if(i == 0){
	 choice2 = estate;  //Gain non treasure card
	 printf("Trashing treasure for a non-treasure card worth less in cost than itself\n");
	 assertTrue(-1,r); 
      }

      else if( i== 1){
	 choice2 = council_room; //Gain a card value higher than +3
	 printf("Trashing treasure for non-treasure card worth more in cost than itself\n");
	 assertTrue(-1,r); 
      }

      else if( i==2){
	 choice2 = gold;
	 printf("Trashing a treasure card (silver) for gold\n"); 
	 assertTrue(0,r); 
      }
      else if( i==3){
	 choice2 = copper;
	 printf("Trashing a treasure card (silver) for copper\n");
	 assertTrue(-1,r); 
      }
      else if( i==4){
	 choice1 = 8;
	 choice2 = great_hall;
	 printf("Trashing a non-treasure card (gardens) for a card less than itself\n");

	 assertTrue(-1,r); 
      }

      printf("Card we are trashing %d\n", handCard(choice1, &state));
      r = Mine(choice1, choice2, currentPlayer, &state, handPos); 
      printf("Card we wish to obtain (enum value): %d\n", choice2);
      printf("Cards in hand: ");

      for( j=0; j<9; j++){
	 printf(" %d", handCard(j, &state)); 
      }
      printf("\n\n");
   }
}

