WARNINGS=-Wall -Wextra
LINKERS=`pkg-config raylib --libs`
CFLAGS=-O3
SRC=../src/
ifdef DEBUG
	CFLAGS=-g
endif

compile:
	gcc -c $(SRC)main.c $(LINKERS) $(CFLAGS) $(WARNINGS)
	gcc -c $(SRC)input.c $(LINKERS) $(CFLAGS) $(WARNINGS)
	gcc -c $(SRC)draw.c $(LINKERS) $(CFLAGS) $(WARNINGS)
	gcc -c $(SRC)game.c $(LINKERS) $(CFLAGS) $(WARNINGS)
	gcc main.o input.o draw.o game.o -o gameoflife $(LINKERS) $(CFLAGS) $(WARNINGS)

clean::
	rm *.o
	rm gameoflife
