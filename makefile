.PHONY: all clean test

CC=gcc

all:
	cd lib && make
	cd beta && make

test:
	cd vaspC && make test
	cd beta && make test

clean:
	cd vaspC && make clean
	cd beta && make clean
