CC = gcc
CFLAGS = -Wall -g

all: part1

part1.o: part1.c
	$(CC) $(CFLAGS) -c part1.c

part1: part1.o
	$(CC) $(CFLAGS) -o part1 part1.o -lm

clean:
	rm -f *.o part1