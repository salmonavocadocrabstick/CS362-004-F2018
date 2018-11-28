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

randomTest1: randomtestcard1.c dominion.o rngs.o
	echo "Results of Test 1:" > randomtestcard1.out
	gcc -o randomTest1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomTest1 >> randomtestcard1.out
	gcov -b -f dominion.c | grep "smithy_effect_bug" -B 0 -A 5 >> randomtestcard1.out

randomTest2: randomtestcard2.c dominion.o rngs.o
	echo "Results of Test 2:" > randomtestcard2.out
	gcc -o randomTest2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomTest2 >> randomtestcard2.out
	gcov -b -f dominion.c | grep "council_room_effect_bug" -B 0 -A 5 >> randomtestcard2.out

randomTest3: randomtestadventurer.c dominion.o rngs.o
	echo "Results of Test 3:" > randomtestadventurer.out
	gcc -o randomTest3 -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomTest3 >> randomtestadventurer.out
	gcov -b -f dominion.c | grep "adventurer_effect_bug" -B 0 -A 5 >> randomtestadventurer.out

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

# runtests: testDrawCard 
# 	./testDrawCard &> unittestresult.out
# 	gcov dominion.c >> unittestresult.out
# 	cat dominion.c.gcov >> unittestresult.out

# test: randomTest 
# 	./randomTest


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomTest2 randomTest3 randomTest1 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
