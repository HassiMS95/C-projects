CC = gcc
CFLAGS = -Wall -g

all: part1 part2 part3

part1.o: part1.c
	$(CC) $(CFLAGS) -c part1.c

part1: part1.o
	$(CC) $(CFLAGS) -o part1 part1.o -lm

part2.o: part2.c
	$(CC) $(CFLAGS) -c part2.c

part2: part2.o
	$(CC) $(CFLAGS) -o part2 part2.o -lm

part3.o: part3.c
	$(CC) $(CFLAGS) -c part3.c

part3: part3.o
	$(CC) $(CFLAGS) -o part3 part3.o -lm

clean:
	rm -f *.o part1 part2 part3