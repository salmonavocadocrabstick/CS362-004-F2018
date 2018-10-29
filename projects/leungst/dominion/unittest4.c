#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"


int main(){


	//Test target: getCost 

	// int x, y, z;

	// //For Initializing game
	// int numPlayers = 2;
	// int currentPlayer = 0;
	// int seed = 500;

	// //Base state
	// struct gameState s;
	// struct gameState *state = &s;
	// memset(state, 0, sizeof(struct gameState));

	// //Test state
	// struct gameState t;
	// struct gameState *testState = &t;
	// memset(state, 0, sizeof(struct gameState));

	//int k[10] = {adventurer, smithy, great_hall, minion, mine, cutpurse,
	//		sea_hag, tribute, province, council_room};

	printf("Initiating Test game....\n");

 	//Initiate a game state for base
	//initializeGame(numPlayers, k, seed, state);

	int costCurse = getCost(curse);
	int costEstate = getCost(estate);
	int costDuchy = getCost(duchy);
	int costFeast = getCost(feast);
	int costSmithy = getCost(smithy);

	printf("Testing GetCost()....\n");
	printf("-----------------------------------------------------\n");

	printf("Curse: %d\t|\texpected %d\n", costCurse, 0);
	printf("Estate: %d\t|\texpected %d\n", costEstate, 2);
	printf("Duchy: %d\t|\texpected %d\n", costDuchy, 5);
	printf("Feast: %d\t|\texpected %d\n", costFeast, 4);	
	printf("Smithy: %d\t|\texpected %d\n", costSmithy, 4);

	return 0;
}

