CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unitTests: unittest1.c unittest2.c unittest3.c dominion.o rngs.o

	echo "-----------------------------------------------------" > unittestresults.out
	echo "Results for Dominion Function Unit Test:" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "unittest1.c " >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out


	echo "" >> unittestresults.out
	echo "-----------------------------------------------------" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "unittest2.c - fullDeckCount():" >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	echo "" >> unittestresults.out
	echo "-----------------------------------------------------" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "unittest3.c - getCost(int):" >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	echo "" >> unittestresults.out
	echo "-----------------------------------------------------" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "unittest4.c - getCost(int):" >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	#cat unittestresults.out
	#echo "unittest2.c:" >> unittestresults.out
	#gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	#./unittest2 >> unittestresults.out
	#gcov -b dominion.c >> unittestresults.out

cardTests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "" >> unittestresults.out
	echo "-----------------------------------------------------" >> unittestresults.out
	echo "Results for Dominion Card Effects Unit Test:" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "cardtest1.c - SMITHY:" >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardTest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardTest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	echo "" >> unittestresults.out

	echo "-----------------------------------------------------" >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "cardtest2.c: COUNCIL_ROOM" >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardTest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardTest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	echo "-----------------------------------------------------" >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "cardtest3.c: GREAT_HALL" >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardTest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardTest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	echo "-----------------------------------------------------" >> unittestresults.out
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out
	echo  "cardtest4.c: ADVENTURER " >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardTest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardTest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "" >> unittestresults.out
	echo "" >> unittestresults.out

	cat unittestresults.out
	#echo "unittest2.c:" >> unittestresults.out
	#gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	#./unittest2 >> unittestresults.out
	#gcov -b dominion.c >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unitTests cardTests

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
