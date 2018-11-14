#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

int checkTarget(int currentPlayer, struct gameState* testGame, int handPos, int handCount, int deckCount);
int** checkState(int currentPlayer, struct gameState* testGame, int totalParameters);
int checkDiscarded(int currentPlayer, struct gameState* testGame);
void fillDeckWithCard(int currentPlayer, struct gameState* testGame, int card, int deckCount);
int compareStates(int** beforeState, int** afterState, int p, int numPlayers, int parameters);



int main(){

	//Test Target:
	int testTarget = council_room;
	printf("Testing [ COUNCIL_ROOM ]  \n");


	//base variables to set up the test
	int x, i, n, r, p, numPlayers, handPos;
	int testResult = -10;
	int compareBeforeAfter = 0;

	//Testing counters
	int totalTests = 550;

	//Expecting: +4 cards, +1 buy
	//States to check
	int totalParameters = 3;
	int deckCount, discardCount, handCount;

	//Setting up the game
	int seed = 500;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall };
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

		t.numBuys = floor(Random() * MAX_HAND); //Maximum possible: assuming each card +1 buy
		printf("Current Buy Count %d\n", t.numBuys);
		
		t.numActions = floor(Random() * MAX_HAND * 2); //Maximum possible: assuming each card + no more than 2
		printf("Current Action Count %d\n", t.numActions);


		handPos = floor(Random() * t.handCount[p]); //randomize position of target card.
		t.hand[p][handPos] = testTarget;

		//check state - before
		beforeState = checkState(numPlayers, t_ptr, totalParameters);

		//check target: council_room
		testResult = checkTarget(p, t_ptr, handPos, t.handCount[p], t.deckCount[p]);

		//check state - again.
		afterState = checkState(numPlayers, t_ptr, totalParameters);

		//Compare the two states.
		printf("Testing if other players are affected: \n");
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


int checkTarget(int currentPlayer, struct gameState* testGame, int handPos, int count, int deckCount){

	//Expecting: +4 cards, +1 buy
	int old_deckCount = deckCount;
	int old_handCount = count;
	int old_numBuys = testGame->numBuys;
	int old_numActions = testGame->numActions;
	int new_deckCount, new_handCount, new_numBuys, new_numActions;

	//Set to TRUE if found
	int bugFound = FALSE;

	//First check functions/variables that are used by test target
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

			//Change target card here==================:
			council_room_effect_bug(currentPlayer, testGame, handPos);

			//==========================================

			//Check new variables here
			new_deckCount = testGame->deckCount[currentPlayer];
			new_handCount = testGame->handCount[currentPlayer];
			new_numActions = testGame->numActions;
			new_numBuys = testGame->numBuys;

			//Check if the new varaibles match as expected
			if(old_numBuys +1 != new_numBuys){
				printf("\t...FAILED \n");
				printf("\t\t...numBuys %d\n", new_numBuys);
				
				bugFound = TRUE;
			}
			if(old_deckCount - 5 != new_deckCount){
				printf("\t...FAILED \n");
				printf("\t\t...deck count %d\n", new_deckCount);
				bugFound = TRUE;
			}
			if(old_handCount + 5 != new_handCount){	
				printf("\t...FAILED \n");
				printf("\t\t... hand count %d\n", new_handCount);
				bugFound = TRUE;
			}
			if(old_numActions != new_numActions){
				printf("\t...FAILED \n");
				printf("\t\t...numActions %d\n", new_numActions);
				bugFound = TRUE;
			}


		}
		else{
			printf("\t...FAILED \n");
			printf("!! Something happened to the discard function, aborting\n");
			bugFound = TRUE;
		}
	}
	else{
		printf("\t...FAILED \n");
		printf("!! Something happened in drawCard() function. Aborting.\n");
		bugFound = TRUE;
	}



	if(bugFound == TRUE){

		return -1;
	}
	

	printf("\t...PASSED\n");
	return 0;
}

int** checkState(int numPlayers, struct gameState* testGame, int totalParameters){

	//Counters
	int x, y, z, a;

	//create matrix: numPlayers * 3
	int **stateCheck = (int **)malloc(totalParameters * sizeof(int*));
	for (a = 0; a < totalParameters; a++){

		stateCheck[a] = (int*)malloc(numPlayers * sizeof(int));
	}
	memset(stateCheck, 0, sizeof(int)* totalParameters * numPlayers);

	//=======================Change for each card ========================/

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


	//=======================Change for each card ========================/

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