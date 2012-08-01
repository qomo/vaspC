.phony: clean test

.SUFFIXES:
	MAKEFLAGS += -r
CC=gcc

vaspC.a: outcar.o potcar.o list.o lattice.o line.o element.o poscar.o vmath.o field.o gradient.o vacuum.o insort.o swap.o incar.o incar.tab.o incar.lex.o hash.o potcar.o potcar.tab.o potcar.lex.o util.o
	ar rcs $@ $^	

%.o: %.c
	$(CC) -g  -Wall -c $^

incar.tab.o incar.lex.o incar.o: incar.y incar.l incar.c
	bison -d -W incar.y
	flex -o incar.lex.c incar.l
	gcc -c -W incar.lex.c incar.c incar.tab.c   

potcar.tab.o potcar.lex.o potcar.o: potcar.y potcar.l potcar.c
	bison -d -W potcar.y
	flex -o potcar.lex.c potcar.l
	gcc -c -W potcar.lex.c potcar.c potcar.tab.c   

test: vaspC.a
	cd unitest && make test

clean:
	rm -f *.o vaspC.a *.lex.c *.tab.c *.tab.h
