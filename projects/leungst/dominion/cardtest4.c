/***************************************************
	OSU CS362 - Assignment 3
	
	Stephanie Leung			28th Oct 2018

	Cardteset4.c - Adventurer
	
	*Continuously draw from deck until 2 treasure cards are reviewed
	*Only two treasure cards are added to the hand.

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

	//Test target: 
	int testTarget = adventurer;

	//Information on testTarget
	int newCards = 0;
	int discarded = 1;
	int extraCoins = 2;
	//int shuffleCards = 0;
	int extraBuys = 0;
	int extraActions = 0;
	//int treasureCards = 2;

	int x, y, z;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;

	//For Initializing game
	int numPlayers = 2;
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
			sea_hag, tribute, smithy, council_room};

	printf("Initiating Test game....\n");

 	//Initiate a game state for base
	initializeGame(numPlayers, k, seed, state);

 	//Player decks: 3 cards of target, 7 cards of coppers
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
		  	state->deck[z][x] = testTarget;
		  	state->deckCount[z]++;    
		}

		state->handCount[z] = 0;
		state->discardCount[z] = 0;

		for(y = 0; y < 5; y++){
		  
		  int drawCardResult = drawCard(z, state);

		  if(drawCardResult == -1){

		    printf("Drawcard: something is wrong\n");
		  }
		}

		testState->hand[z][handpos] = testTarget;
	}



	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));
	choice1 = 1;

	//Setting up first move
	int currentPlayer = 0;

	int tCount_beforeDraw=0;
	for(x = 0; x < testState->handCount[currentPlayer]; x++){

		if(testState->hand[currentPlayer][x] == copper){

			tCount_beforeDraw++;
		}

	}

	//Run a check on current coin count
	//int currentCoin = testState->coins;


	//Run card effect.
	cardEffect(testTarget, choice1, choice2, choice3, testState, handpos, &bonus);


	printf("Testing Counters....\n");
	printf("-----------------------------------------------------\n");
	printf("\t- Hand count = %d\t|\texpected = %d \n", 
		testState->handCount[currentPlayer], 
		state->handCount[currentPlayer] + newCards - discarded);

	printf("\t- Deck count = %d\t|\texpected = %d \n",
		testState->deckCount[currentPlayer],
		state->deckCount[currentPlayer] - newCards);

	printf("\t- Coin amount = %d\t|\texpected = %d \n",
		testState->coins,
		state->coins + extraCoins);

	//Count #treasure cards
	int tCount=0;
	for(x = 0; x < testState->handCount[currentPlayer]; x++){

		if(testState->hand[currentPlayer][x] == copper){

			tCount++;
		}
	}
	printf("\t - # treasure cards = %d\t|\texpected = %d\n", 
		tCount, 
		tCount_beforeDraw+2);


	// printf("\t- Discarded count = %d\t|\texpected = %d\n",
	// 	testState->discardCount[currentPlayer],
	// 	state->discardCount[currentPlayer] + discarded);

	printf("\t- Numbuy = %d\t\t|\texpected = %d\n",
		testState->numBuys,
		state->numBuys + extraBuys );

	printf("\t- NumAction = %d\t\t|\texpected = %d\n",
		testState->numActions,
		state->numActions+extraActions);

	printf("\t- Score = %d\t\t|\texpected = %d\n",
		scoreFor(0, testState),
		scoreFor(0, state));

	printf("\n\n");


	//Copy base over to test game.
	memcpy(testState, state, sizeof(struct gameState));

	//Setting up first move
	currentPlayer = 0;

	//Run a check on current coin count
	int currentCoin = testState->coins;
	
	printf("Testing in case of 0 treasure card exists.....\n");
	printf("-----------------------------------------------------\n");

	//removing all treasures
	for( x = 0; x < testState->handCount[currentPlayer]; x++){

		if( testState->hand[currentPlayer][x] == copper ){

			testState->hand[currentPlayer][x] = -1;
		}

	}
	for( y = 0; y < testState->deckCount[currentPlayer]; y++){

		if(testState->deck[currentPlayer][y] == copper){

			testState->deck[currentPlayer][y] = -1;
		}
	}

	cardEffect(testTarget, choice1, choice2, choice3, testState, handpos, &bonus);

	printf("\t- Hand count = %d\t|\texpected = %d \n", 
		testState->handCount[currentPlayer], 
		state->handCount[currentPlayer] + newCards - discarded);

	printf("\t- Deck count = %d\t|\texpected = %d \n",
		testState->deckCount[currentPlayer],
		state->deckCount[currentPlayer] - newCards);

	printf("\t- Coin amount = %d\t|\texpected = %d \n",
		testState->coins,
		state->coins + extraCoins);

	//Count #treasure cards
	tCount=0;
	for(x = 0; x < testState->handCount[currentPlayer]; x++){

		if(testState->hand[currentPlayer][x] == copper){

			tCount++;
		}
	}
	printf("\t - # treasure cards = %d\t|\texpected = %d\n", 
		tCount, 
		tCount_beforeDraw+2);


	// printf("\t- Discarded count = %d\t|\texpected = %d\n",
	// 	testState->discardCount[currentPlayer],
	// 	state->discardCount[currentPlayer] + discarded);

	printf("\t- Numbuy = %d\t\t|\texpected = %d\n",
		testState->numBuys,
		state->numBuys + extraBuys );

	printf("\t- NumAction = %d\t\t|\texpected = %d\n",
		testState->numActions,
		state->numActions+extraActions);

	printf("\t- Score = %d\t\t|\texpected = %d\n",
		scoreFor(0, testState),
		scoreFor(0, state));

	printf("\n\n");


	return 0;
}

