CompilaObjeto = gcc -g -c
all: fila.o inout.o main.o clientes.o simulador.o headers.h
	gcc -g fila.o inout.o main.o clientes.o simulador.o -o sim_senhas
#"make GeraArquivos" Para criar o programa que gera arquivo de saida com Clientes
GeraArquivos: GeraArquivos.o inout.o clientes.o fila.o headers.h
	gcc -g GeraArquivos.o inout.o clientes.o fila.o -o Teladeclientes
fila.o: fila.c
	$(CompilaObjeto) fila.c 
inout.o: inout.c
	$(CompilaObjeto) inout.c 
main.o: main.c
	$(CompilaObjeto) main.c
clientes.o: clientes.c
	$(CompilaObjeto) clientes.c
GeraArquivos.o: GeraArquivos.c
	$(CompilaObjeto) GeraArquivos.c
simulador.o: simulador.c
	$(CompilaObjeto) simulador.c
clear:
	rm -f inout.o fila.o GeraArquivos.o main.o clientes.o 