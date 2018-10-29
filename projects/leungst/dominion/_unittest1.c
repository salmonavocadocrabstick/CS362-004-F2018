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
	int numPlayers = 2;
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


	printf("Testing Case: Province Supply Count changes....\n");
	printf("-----------------------------------------------------\n");

	testState->supplyCount[province] = 0;
	printf("Province Count: %d\t|\tGameover: ", testState->supplyCount[province]);
	int test1 = isGameOver(testState);

	testTorF(test1);

	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));

	testState->supplyCount[province] = 10;
	printf("Province Count: %d\t|\tGameover: ", testState->supplyCount[province]);
	int test2 = isGameOver(testState);

	testTorF(test2);

	printf("Testing Case: Other supply count changes....\n");
	printf("-----------------------------------------------------\n");

	testState->supplyCount[0] = 0;
	testState->supplyCount[1] = 0;
	testState->supplyCount[2] = 0;
	printf("3 Kingdom cards counts set to 0\t|\tGameover: ");
	int test3 = isGameOver(testState);

	testTorF(test3);

	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));

	testState->supplyCount[0] = 0;
	testState->supplyCount[1] = 0;
	printf("2 Kingdom cards counts set to 0\t|\tGameover: ");
	int test4 = isGameOver(testState);

	testTorF(test4);

	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));

	testState->supplyCount[0] = 0;
	testState->supplyCount[1] = 0;
	testState->supplyCount[2] = 0;
	testState->supplyCount[3] = 0;
	printf("4 Kingdom cards counts set to 0\t|\tGameover: ");
	int test5 = isGameOver(testState);

	testTorF(test5);

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
