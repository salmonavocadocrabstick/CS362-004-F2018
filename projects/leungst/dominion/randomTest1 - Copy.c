#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <assert.h>


int checkSmithy(int currentPlayer, struct gameState* testGame, int handPos, int handCount, int deckCount);
int** checkState(int currentPlayer, struct gameState* testGame);
int checkDiscarded(int currentPlayer, struct gameState* testGame);
void fillDeckWithCard(int currentPlayer, struct gameState* testGame, int card, int deckCount);
int compareStates(int** beforeState, int** afterState, int p, int numPlayers, int parameters);



int main(){

	//base variables to set up the test
	int x, i, n, r, p, deckCount, discardCount, handCount, numPlayers, handPos;
	int seed = 500;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall };


	int testTarget = smithy;
	int testResult = -10;
	int compareBeforeAfter = 0;
	int totalTests = 5000;

	struct gameState t;
	struct gameState* t_ptr = &t;
	memset(t_ptr, 0, sizeof(struct gameState));

	//Initiate a game state for base
	initializeGame(numPlayers, k, seed, t_ptr);


	numPlayers = floor(Random() * 4);

	for (x = 0; x < numPlayers; x++){

		p = floor(Random() * 2);
		t.deckCount[p] = floor(Random() * MAX_DECK);
		t.discardCount[p] = floor(Random() * MAX_DECK);
		t.handCount[p] = floor(Random() * MAX_HAND);

	}


	//For state checks
	//beforeState[3][numPlayers];
	int **afterState = NULL;
	int **beforeState = NULL;

	SelectStream(1);
	PutSeed(5);



	for ( n = 0; n < totalTests; n++){
	
		printf("\n-------------------------------------\n");
		p = n % 4;
		printf("Current Player: %d\n", p);
		t.deckCount[p] = floor(Random() * MAX_DECK);
		printf("Current Deck Count: %d\n", t.deckCount[p]);
		
		fillDeckWithCard(p, t_ptr, testTarget, t.deckCount[p]);

		t.discardCount[p] = floor(Random() * MAX_DECK);
		printf("Current Discard Count: %d\n", t.discardCount[p] );
		t.handCount[p] = floor(Random() * MAX_HAND);
		printf("Current Hand Count: %d\n", t.handCount[p]);

		handPos = floor(Random() * t.handCount[p]); //randomize position of smithy.

		t.hand[p][handPos] = testTarget;
		//check state - before
		beforeState = checkState(numPlayers, t_ptr);

		//check smithy
		testResult = checkSmithy(p, t_ptr, handPos, t.handCount[p], t.deckCount[p]);
		printf("After test result, smith results: %d\n", testResult);

		//check state - again.
		afterState = checkState(numPlayers, t_ptr);

		//Compare the two states.
		printf("Checking if other players are affected: \n");
		compareBeforeAfter = compareStates(beforeState, afterState, p, numPlayers, 3);
		if(compareBeforeAfter == 0){

			printf("\t...PASSED\n");
		}
		else{
			printf("\t...FAILED \n");
		}

	}




	return 0;
}

int compareStates(int** beforeState, int** afterState, int p, int numPlayers, int parameters){

	//Compare the two states. Only P's states should have changed. 
	//If not, return -1.
	int x, y;
	for( x = 0; x < parameters; x++){

		for(y = 0; y < numPlayers; y++){


			if(beforeState[x][y] == afterState[x][y]){ 

				continue;

			}
			else{ 

				// printf("X is %d\n", x);
				// printf("Y is %d\n", y);

				// printf("Before: %d\n", beforeState[x][y]); 
				// printf("After: %d\n", afterState[x][y]);
				if( y == p){

					continue;
				}
				else{

					//something else changed other than the current player. Report
					printf("Mismatch found, card has changed states of other players unexpectedly\n");

					return -1;
				}
			}		

		}

	}


	return 0;

}


int checkSmithy(int currentPlayer, struct gameState* testGame, int handPos, int count, int deckCount){

	//deck should be 3 cards less than original
	//handCount should be +3
	int old_deckCount = deckCount;
	int old_handCount = count;
	int new_deckCount, new_handCount;

	//First check functions that are used by test target
	//For current target:
	// 1. drawcard
	// 2. discardCard
	printf("Checking functions used by test target\n");
	printf("drawCard: \n");
	drawCard(currentPlayer, testGame);
	if(testGame->handCount[currentPlayer] == count + 1 ){
		printf("\t...PASSED\n");
		printf("discardCard: \n");
		discardCard(count, currentPlayer, testGame, 0);

		if(testGame->handCount[currentPlayer] == count ){
			printf("\t...PASSED\n");
			printf("Target card: \n");
			smithy_effect_bug(currentPlayer, testGame, handPos);

			new_deckCount = testGame->deckCount[currentPlayer];
			new_handCount = testGame->handCount[currentPlayer];

			if(old_deckCount - 3 != new_deckCount){
				printf("\t...FAILED \n");
				printf("old deck count %d\n", old_deckCount);
				printf("new deck count %d\n", new_deckCount);
				return -1;
			}
			else if(old_handCount + 3 != new_handCount){	
				printf("\t...FAILED \n");
				printf("old hand count %d\n", old_handCount);
				printf("new hand count %d\n", new_handCount);
				return -1;
			}
		}
		else{
			printf("\t...FAILED \n");
			printf("!! Something happened to the discard function, aborting\n");
			return -1;
		}
	}
	else{
		printf("\t...FAILED \n");
		printf("!! Something happened in drawCard() function. Aborting.\n");
		return -1;
	}


	

	printf("\t...PASSED\n");
	return 0;
}

int** checkState(int numPlayers, struct gameState* testGame){

	//Counters
	int x, y, z, a;

	//create matrix: numPlayers * 3
	int **stateCheck = (int **)malloc(3 * sizeof(int*));
	for (a = 0; a < 3; a++){

		stateCheck[a] = (int*)malloc(numPlayers * sizeof(int));
	}
	memset(stateCheck, 0, sizeof(int)* 3 * numPlayers);


	//everyone's deckCount
	for( x = 0; x < numPlayers; x++){

		stateCheck[0][x] = testGame->deckCount[x];
	}

	//everyone's handCount
	for( y = 0; y < numPlayers; y++){

		stateCheck[1][y] = testGame->handCount[y];
	}

	//everyone's discardCount
	for( z = 0; z < numPlayers; z++){

		stateCheck[2][z] = testGame->discardCount[z];
	}

	//change to returning the whole array.
	return stateCheck;
}

int checkDiscarded(int currentPlayer, struct gameState* testGame){

	//should be able to find the smithy card.
	return 0;
}


void fillDeckWithCard(int currentPlayer, struct gameState* testGame, int card, int deckCount){

	int x;

	for ( x = 0; x < deckCount; x++ ){

		testGame->deck[currentPlayer][x] = card;
	}
}