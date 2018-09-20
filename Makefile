all: fila.o inout.o main.o clientes.o
	gcc -g fila.o inout.o main.o clientes.o
fila.o: fila.c
	gcc -g -c fila.c 
inout.o: inout.c
	gcc -g -c inout.c 
main.o: main.c
	gcc -g -c main.c
clientes.o: clientes.c
	gcc -g -c clientes.c
clear:
	rm inout.o func.o fila.o 