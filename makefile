CC=gcc
CFLAGS= -Wall -pedantic -g
LDLIBS= -lm


.PHONY: run_test
run_test: clean test_unbounded
	./out/test_unbounded

run_calc: clean calc_unbounded
	./out/calc_unbounded

test_unbounded : test_unbounded.c unbounded_int.c
	$(CC) $(CFLAGS) test_unbounded.c -lm -o out/test_unbounded

calc_unbounded : calc_unbounded_int.c unbounded_int.c
	$(CC) $(CFLAGS) calc_unbounded_int.c -lm -o out/calc_unbounded

clean :
	rm -rf /out/*
