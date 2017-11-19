CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)


testKim: dominion.o cardtest1.c cardtest2.c randomtestadventurer.c randomtestcard1.c
	echo "Results for running dominion tests:">kimtestresults.out
	echo "cardtest1.c:" >>kimtestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	./cardtest1 >> kimtestresults.out
	gcov dominion.c >> kimtestresults.out
	echo "cardtest2.c:" >>kimtestresults.out
	gcc -o cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)
	./cardtest2 >> kimtestresults.out
	gcov dominion.c >> kimtestresults.out
	echo "randomtestadventurer.c:" >>kimtestresults.out
	gcc -o randomtestadventurer dominion.o rngs.o randomtestadventurer.c $(CFLAGS)
	./randomtestadventurer >> kimtestresults.out
	gcov dominion.c >> kimtestresults.out
	echo "randomtestcard1.c:" >>kimtestresults.out
	gcc -o randomtestcard1 dominion.o rngs.o randomtestcard1.c $(CFLAGS)
	./randomtestcard1 >> kimtestresults.out
	gcov dominion.c >> kimtestresults.out
	cat dominion.c.gcov >>kimtestresults.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out cardtest1 cardtest2 randomtestadventurer randomtestcard1 
