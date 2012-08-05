.phony: clean test

CC= gcc

unitest: unitest.c  unitest.h ut_outcar.c ut_potcar.c ut_list.c ut_lattice.c ut_swap.c ut_insort.c ut_gradient.c ut_vacuum.c ut_elem.c  ut_line.c  ut_poscar.c ut_vmath.c ut_field.c ut_incar.c ut_hash.c ut_keyword.c ../vaspC.a  
	$(CC) -I.. -lm -Wall `pkg-config --cflags --libs glib-2.0` -o $@ $^

test: unitest
	./unitest

clean:
	rm -f unitest
