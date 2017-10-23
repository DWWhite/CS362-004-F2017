CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

runtest: testme
	./testme &> testresult.out

coverage: testme.c
	gcov testme.c >> testresult.out
	cat testme.c.gcov >> testresult.out

clean:
	rm -rf *.o testme *.gcov *.gcda *.gcno *.dSYM *.out
