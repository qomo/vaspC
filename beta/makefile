.phony: test clean
CC= gcc

beta.x: main.c beta.c ../vaspC/vaspC.a
	$(CC) -I../vaspC/ -lm -Wall -o $@ $^

test:
	cd unitest && make test

clean:
	rm -f beta.x
