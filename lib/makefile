.phony: clean test

.SUFFIXES:
	MAKEFLAGS += -r
CC=gcc

vaspC.a: outcar.o potcar.o list.o lattice.o line.o element.o poscar.o vmath.o field.o gradient.o vacuum.o insort.o swap.o hash.o potcar.o potcar.tab.o potcar.lex.o util.o incar.o incar.tab.o incar.lex.o keyword.tab.o keyword.lex.o keyword.o outcar.tab.o outcar.lex.o outcar.o kpoints.o kp_mesh.tab.o kp_mesh.lex.o kp_line.tab.o kp_line.lex.o kp_grid.tab.o kp_grid.lex.o
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

keyword.tab.o keyword.lex.o keyword.o: keyword.y keyword.l keyword.c
	bison -d -W keyword.y
	flex -o keyword.lex.c keyword.l
	gcc -c -W keyword.lex.c keyword.c keyword.tab.c   

outcar.tab.o outcar.lex.o outcar.o: outcar.y outcar.l outcar.c
	bison -d -W outcar.y
	flex -o outcar.lex.c outcar.l
	gcc -c -W outcar.lex.c outcar.c outcar.tab.c   

kp_mesh.tab.o kp_mesh.lex.o : kp_mesh.y kp_mesh.l
	bison -d -W kp_mesh.y
	flex -o kp_mesh.lex.c kp_mesh.l
	gcc -c -W kp_mesh.lex.c kp_mesh.tab.c   

kp_line.tab.o kp_line.lex.o : kp_line.y kp_line.l
	bison -d -W kp_line.y
	flex -o kp_line.lex.c kp_line.l
	gcc -c -W kp_line.lex.c kp_line.tab.c   

kp_grid.tab.o kp_grid.lex.o : kp_grid.y kp_grid.l
	bison -d -W kp_grid.y
	flex -o kp_grid.lex.c kp_grid.l
	gcc -c -W kp_grid.lex.c kp_grid.tab.c   

test: vaspC.a
	cd unitest && make test

clean:
	rm -f *.o vaspC.a *.lex.c *.tab.c *.tab.h
