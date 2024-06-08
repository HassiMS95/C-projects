project3Exe: main.o champion.o
	gcc main.o route-records.o -o project3Exe
main.o : main.c champion.h
	gcc -c main.c -o main.o
champion.o : champion.c champion.h
	gcc -c champion.c -o champion.o
clean :
	rm -rf *.o
	rm project3Exe