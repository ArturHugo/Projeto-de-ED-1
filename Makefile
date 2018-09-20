all: fila.o inout.o main.o cliente.o
	gcc -g fila.o inout.o main.o cliente.o
fila.o: fila.c
	gcc -g -c fila.c 
inout.o: inout.c
	gcc -g -c inout.c 
main.o: main.c
	gcc -g -c main.c
cliente.o: cliente.c
	gcc -g -c cliente.c
clear:
	rm inout.o func.o fila.o 