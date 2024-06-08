myprogram: main.o route-records.o
	gcc main.o route-records.o -o myprogram
main.o : main.c route-records.h
	gcc -c main.c -o main.o
route-records.o : route-records.c route-records.h
	gcc -c route-records.c -o route-records.o
clean :
	rm -rf *.o
	rm myprogram