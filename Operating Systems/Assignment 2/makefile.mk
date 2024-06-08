CC = gcc
CFLAGS = -Wall -g

all: prog 

clean:
	rm -f *.o prog

prog: prog.c prog.h
    $(CC) $(CFLAGS) -o prog prog.c