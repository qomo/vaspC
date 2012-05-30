.phony: clean test

CC=gcc

vaspC.a: outcar.o potcar.o list.o lattice.o line.o element.o poscar.o vmath.o field.o gradient.o vacuum.o insort.o swap.o
	ar rcs $@ $^	

%.o: %.c
	$(CC) -g  -Wall -c $^

test: vaspC.a
	cd unitest && make test

clean:
	rm -f *.o vaspC.a
