.phony: clean test

CC= gcc

VASPC_PATH=/home/huang/tool/C/vaspC

unitest: ut_beta.c ../beta.c $(VASPC_PATH)/vaspC.a
	$(CC) -I$(VASPC_PATH) -I.. -lm -Wall `pkg-config --cflags --libs glib-2.0` -o $@ $^

test: unitest
	./unitest

clean:
	rm -f unitest
