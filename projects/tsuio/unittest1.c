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


	//Test target: int supplyCount(int card, struct gameState *state)


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

	// //Copy base over to test game.
	// memcpy(testState, state, sizeof(struct gameState));

	int k[10] = {adventurer, smithy, great_hall, minion, mine, cutpurse,
			sea_hag, tribute, province, council_room};

	printf("Initiating Test game....\n");

 	//Initiate a game state for base
	initializeGame(numPlayers, k, seed, state);



	printf("Testing Case: Supply Count - default....\n");
	printf("-----------------------------------------------------\n");

	int test1 = supplyCount(adventurer, testState);
	int test2 = supplyCount(smithy, testState);
	int test3 = supplyCount(gardens, testState);
	int test4 = supplyCount(great_hall, testState);
	int test5 = supplyCount(minion, testState);
	int test6 = supplyCount(ambassador, testState);

	printf("Adventurer: \t%d\n", test1);
	printf("smithy: \t%d\n", test2);
	printf("great_hall: \t%d\n", test4);
	printf("minion: \t%d\n", test5);

	printf("K cards that are not currently used: \n");
	printf("gardens: \t%d\n", test3);
	printf("gardens: \t%d\n", test6);
	printf("\n\n");

	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));
	printf("Testing Case: filling up the supplies...\n");

	test1 = supplyCount(adventurer, testState);
	test2 = supplyCount(smithy, testState);
	test3 = supplyCount(gardens, testState);
	test4 = supplyCount(great_hall, testState);
	test5 = supplyCount(minion, testState);
	test6 = supplyCount(ambassador, testState);

	printf("Adventurer: \t%d\n", test1);
	printf("smithy: \t%d\n", test2);
	printf("great_hall: \t%d\n", test4);
	printf("minion: \t%d\n", test5);

	printf("K cards that are not currently used: \n");
	printf("gardens: \t%d\n", test3);
	printf("gardens: \t%d\n", test6);
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
