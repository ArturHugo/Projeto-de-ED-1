all: fila.o inout.o func.o
	gcc -g fila.o inout.o func.o
fila.o: fila.c
	gcc -g -c fila.c 
inout.o: inout.c
	gcc -g -c inout.c 
func.o: func.c
	gcc -g -c func.c
clear:
	rm inout.o func.o fila.o 