.phony: clean test

.SUFFIXES:
	MAKEFLAGS += -r
CC=gcc

v2key.x: v2key.o v2key.tab.o v2key.lex.o
	$(CC) -Wall -o $@ $^

v2key.tab.o v2key.lex.o v2key.o: v2key.y v2key.l v2key.c
	bison -d -W v2key.y
	flex -o v2key.lex.c v2key.l
	gcc -c -W v2key.lex.c v2key.c v2key.tab.c   

clean:
	rm -f *.o v2key.lex.c v2key.tab.c v2key.tab.h
