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

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

supplyTest: supplyTest.c dominion.o rngs.o
	gcc -o supplyTest -g  supplyTest.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

cardtest5: cardtest5.c dominion.o rngs.o
	gcc -o cardtest5 -g  cardtest5.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

alltests: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c  cardtest1.c  cardtest2.c  cardtest3.c  cardtest4.c  cardtest5.c  dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest5 -g  cardtest5.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

UpdateCoins: testUpdateCoins
	./testUpdateCoins
	gcov dominion.c >> UpdateCoins.out
	cat dominion.c.gcov >> UpdateCoins.out

testSupply: supplyTest 
	./supplyTest &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

test1: unittest1 
	./unittest1
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test2: unittest2 
	./unittest2 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test3: unittest3 
	./unittest3 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test4: unittest4
	./unittest4 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test5: unittest5
	./unittest5 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test6: cardtest1
	./cardtest1
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test7: cardtest2
	./cardtest2 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test8: cardtest3
	./cardtest3 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test9: cardtest4
	./cardtest4 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

test10: cardtest5
	./cardtest5 
	gcov dominion.c >> unittestresult1.out
	cat dominion.c.gcov >> unittestresult1.out

unittestresults: alltests
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out	
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./cardtest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
