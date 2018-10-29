/***************************************************
	OSU CS362 - Assignment 3
	
	Stephanie Leung			28th Oct 2018

	Unittest2.c - fullDeckCount(int player, int card, struct gameState *state)

	
	*returns cost of a card (supply/treasure/victory)

*************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"


int main(){


	//Test target: fullDeckCount(int player, int card, struct gameState *state) 

	int x, y, z;
    int handpos = 0;

	//For Initializing game
	int numPlayers = 2;
	int currentPlayer = 0;
	int seed = 500;

	//Base state
	struct gameState s;
	struct gameState *state = &s;
	memset(state, 0, sizeof(struct gameState));

	//Test state
	struct gameState t;
	struct gameState *testState = &t;
	memset(state, 0, sizeof(struct gameState));

	int k[10] = {adventurer, smithy, great_hall, minion, mine, cutpurse,
			sea_hag, tribute, province, council_room};

	printf("Initiating Test game....\n");

 	//Initiate a game state for base
	initializeGame(numPlayers, k, seed, state);

	//Player decks: 3 cards of estates, 7 cards of coppers
    //Draw cards simultaneously
	for (z = 0; z < numPlayers; z++)
	{

		state->deckCount[z] = 0;
		for (x = 0; x < 7; x++)
		{
		  	state->deck[z][x] = copper;
		 	 state->deckCount[z]++;
		}

		for (x = 7; x < 10; x++)
		{
		  	state->deck[z][x] = smithy;
		  	state->deckCount[z]++;    
		}

		state->handCount[z] = 0;
		state->discardCount[z] = 0;

	}

	//Make a copy to testState
	memcpy(testState, state, sizeof(struct gameState));


	//All in deck
	printf("Testing Case: Full deck count - default....\n");
	printf("-----------------------------------------------------\n");

	int test1 = fullDeckCount(currentPlayer, copper, testState);

	printf("Checking Copper: %d\t|\tExpected: %d\n", test1, 7);

	int test2 = fullDeckCount(currentPlayer, smithy, testState);
	printf("Checking smithy: %d\t|\tExpected: %d\n", test2, 3);


	//Some in deck
	for(y = 0; y < 5; y++){
		  
		  int drawCardResult = drawCard(currentPlayer, testState);

		  if(drawCardResult == -1){

		    printf("Drawcard: something is wrong\n");
		  }
	}
	printf("\n\nTesting Case: Draw a few cards into hand ....\n");
	printf("-----------------------------------------------------\n");

	test1 = fullDeckCount(currentPlayer, copper, testState);

	printf("Checking Copper: %d\t|\tExpected: %d\n", test1, 7);

	test2 = fullDeckCount(currentPlayer, smithy, testState);
	printf("Checking smithy: %d\t|\tExpected: %d\n", test2, 3);

	//Reset the game state
	memcpy(testState, state, sizeof(struct gameState));



	//Discard a few cards
	printf("\n\nTesting Case: Discard a few cards ....\n");
	printf("-----------------------------------------------------\n");
	//Some in deck
	for(y = 0; y < 5; y++){
		  
		  int drawCardResult = drawCard(currentPlayer, testState);

		  if(drawCardResult == -1){

		    printf("Drawcard: something is wrong\n");
		  }

		 testState->hand[currentPlayer][handpos] = copper;
		 testState->hand[currentPlayer][handpos+1] = smithy;
	}

	int test3 = discardCard(handpos, currentPlayer, testState, 0);
	int test4 = discardCard(handpos, currentPlayer, testState, 0);

	if( test3 != 0||test4 != 0){ printf("SOmething went wrong in discard function\n");}	

	test1 = fullDeckCount(currentPlayer, copper, testState);

	printf("Checking Copper: %d\t|\tExpected: %d\n", test1, 6);

	test2 = fullDeckCount(currentPlayer, smithy, testState);
	printf("Checking smithy: %d\t|\tExpected: %d\n", test2, 2);


	return 0;
}

