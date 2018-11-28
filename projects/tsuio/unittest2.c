#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"


void testTorF(int result);

int main(){


	//Test target: int isGameOver(struct gameState *state)


	//For Initializing game
	int numPlayers = 4;
	//int currentPlayer = 0;
	int seed = 500;

	//Base state
	struct gameState s;
	struct gameState *state = &s;
	memset(state, 0, sizeof(struct gameState));

	//Test state
	struct gameState t;
	struct gameState *testState = &t;
	memset(state, 0, sizeof(struct gameState));

	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));

	int k[10] = {adventurer, smithy, great_hall, minion, mine, cutpurse,
			sea_hag, tribute, province, council_room};

	printf("Initiating Test game....\n");

 	//Initiate a game state for base
	initializeGame(numPlayers, k, seed, state);


	printf("Testing Case: Player turn changes....\n");
	printf("-----------------------------------------------------\n");

	int test1 = testState->whoseTurn = 0;
	int test2 = testState->whoseTurn = -1;
	int test3 = testState->whoseTurn = 999;
	int test4 = testState->whoseTurn = 1;
	int test5 = testState->whoseTurn = 4;

	printf("Set whoseTurn = 0; \t| player's turn: %d\n", test1);
	printf("Set whoseTurn = -1; \t|player's turn: %d\n", test2);
	printf("Set whoseTurn = 999; \t|player's turn: %d\n", test3);
	printf("Set whoseTurn = 1; \t|player's turn: %d\n", test4);
	printf("Set whoseTurn = 4; \t|player's turn: %d\n", test5);

	printf("\n\n");
	return 0;
}

void testTorF(int result){

	if(result == 1){

		printf("TRUE\n\n");
	}
	else if(result == 0){

		printf("FALSE\n\n");
	}
}
