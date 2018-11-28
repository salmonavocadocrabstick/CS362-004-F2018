/***************************************************
	OSU CS362 - Assignment 3
	
	Stephanie Leung			28th Oct 2018

	Unittest3.c - getCost(int cardNumber)

	
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


	//Test target: int getCost(int cardNumber)


	printf("Initiating Test game....\n");

 	//Initiate a game state for base
	//initializeGame(numPlayers, k, seed, state);

	int costCurse = getCost(curse);
	int costEstate = getCost(estate);
	int costDuchy = getCost(duchy);
	int costFeast = getCost(feast);
	int costSmithy = getCost(smithy);
	int costGold = getCost(gold);

	printf("Testing GetCost()....\n");
	printf("-----------------------------------------------------\n");

	printf("Curse: %d\t|\texpected %d\n", costCurse, 0);
	printf("Estate: %d\t|\texpected %d\n", costEstate, 2);
	printf("Duchy: %d\t|\texpected %d\n", costDuchy, 5);
	printf("Feast: %d\t|\texpected %d\n", costFeast, 4);	
	printf("Smithy: %d\t|\texpected %d\n", costSmithy, 4);
	printf("Gold: %d\t|\texpected %d\n", costGold, 6);


	return 0;
}
