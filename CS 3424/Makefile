myprogram: assign4.o
	gcc assign4.o -o myprogram
assign4.o : assign4.c assign4.h
	gcc -c assign4.c -o assign4.o
clean :
	rm -rf *.o
	rm myprogram