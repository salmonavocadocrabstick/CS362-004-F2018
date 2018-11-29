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
	int testTarget = great_hall;

	//Information on testTarget
	int newCards = 1;	
	int discarded = 1;
	int extraCoins = 0;
	int shuffleCards = 0;
	int extraBuys = 0;
	int extraActions = 1;
	int scoreChange = 1;

	int x, y, z;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;

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

	//Run a check on other players' card count.
	int opponentScore = scoreFor(1, testState);

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

	printf("\t- Discarded count = %d\t|\texpected = %d\n",
		testState->discardCount[currentPlayer],
		state->discardCount[currentPlayer] + discarded);

	printf("\t- Numbuy = %d\t\t|\texpected = %d\n",
		testState->numBuys,
		state->numBuys + extraBuys );

	printf("\t- NumAction = %d\t\t|\texpected = %d\n",
		testState->numActions,
		state->numActions+extraActions);

	printf("\t- Score = %d\t\t|\texpected = %d\n",
		scoreFor(0, testState),
		scoreFor(0, state ) + scoreChange);

	printf("\n\n");
	printf("Testing when another copy is gained.....\n");
	printf("-----------------------------------------------------\n");

	//Padding the coins to increase purchase power.
	testState->coins += 3;

	//Checking if there are enough supply for the card.
	int thisSupply = supplyCount(3, testState);
	printf("- Supply of Target: %d\t|\texpected 10\n", thisSupply);

	int purchase = buyCard(k[2],testState);
	if(purchase != 0){

		printf("Buycard: something went wrong in the function\n");
	}
	else{

		printf("Bought 1 target card\n");

	}

	printf("- Current score: = %d\t\t|\texpected = %d\n",
		scoreFor(0, testState),
		scoreFor(0, state)+scoreChange);
	printf("- Oponent score: = %d\t\t|\texpected = %d\n",
		scoreFor(1, testState),
		scoreFor(1, state)+scoreChange);
	printf("- Coin amount = %d\t\t|\texpected = %d \n",
		testState->coins,
		state->coins - 3);

	return 0;
}

