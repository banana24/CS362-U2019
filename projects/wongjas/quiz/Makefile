CFLAGS= -Wall -fpic -coverage -lm -std=c99 -w

testQuiz: testme.c
	gcc -o quiz -g testme.c $(CFLAGS)

runTest: testQuiz
	-./quiz >> output.out 
	gcov testme.c -b -f >> results.out

all: runTest

clean:
	rm -f *.gcov *.gcda *.gcno *.so *.out results.out output.out quiz



