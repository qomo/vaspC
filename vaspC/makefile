.phony: clean test

.SUFFIXES:
	MAKEFLAGS += -r
CC=gcc

vaspC.a: outcar.o potcar.o list.o lattice.o line.o element.o poscar.o vmath.o field.o gradient.o vacuum.o insort.o swap.o incar.o incar.tab.o incar.lex.o
	ar rcs $@ $^	

%.o: %.c
	$(CC) -g  -Wall -c $^

incar.tab.o incar.lex.o incar.o: incar.y incar.l incar.c
	bison -d -W incar.y
	flex -o incar.lex.c incar.l
	gcc -c -W incar.lex.c incar.c incar.tab.c   

test: vaspC.a
	cd unitest && make test

clean:
	rm -f *.o vaspC.a
