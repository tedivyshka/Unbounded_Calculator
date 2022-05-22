CC=gcc
CFLAGS= -Wall -pedantic -g
LDLIBS= -lm


run_test: clean test_unbounded
	./out/test_unbounded

run_calc: clean calc_unbounded
	./out/calc_unbounded

calc_unbounded : clean calc_unbounded_int.o unbounded_int.o
	$(CC) out/calc_unbounded_int.o out/unbounded_int.o -lm -o out/calc_unbounded

test_unbounded : clean test_unbounded.o unbounded_int.o
	$(CC) out/test_unbounded.o out/unbounded_int.o -lm -o out/test_unbounded

calc_unbounded_int.o : clean calc_unbounded_int.c unbounded_int.h
	$(CC) $(CFLAGS) -c calc_unbounded_int.c -lm -o out/calc_unbounded_int.o

test_unbounded.o : clean test_unbounded.c unbounded_int.h
	$(CC) $(CFLAGS) -c test_unbounded.c -lm -o out/test_unbounded.o

unbounded_int.o : clean unbounded_int.c unbounded_int.h
	$(CC) $(CFLAGS) -c unbounded_int.c -lm -o out/unbounded_int.o

clean :
	rm -rdf out/
	mkdir out/
