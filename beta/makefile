.phony: test clean
CC= gcc

beta.x: zone.c main.c beta.c ../lib/vaspC.a
	$(CC) -I../lib/ -lm -Wall -o $@ $^

test:
	cd unitest && make test

clean:
	rm -f beta.x
