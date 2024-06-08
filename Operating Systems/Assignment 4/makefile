CC = gcc
CFLAGS = -Wall -Wextra
JC = javac
JFLAGS = 

all: part1 part2

part1: part1.c
	$(CC) $(CFLAGS) -o part1 part1.c

part2: part2.java
	$(JC) $(JFLAGS) part2.java

clean:
	rm -f part1 part2 *.class