CC= gcc
WFLAGS= -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

all: compilar ejecutar_valgrind 

compilar: juego.c lectura_archivos.c estructuras.c heap.c lista.c personaje.txt gimnasio.txt
	$(CC) *c -o batallas -g $(WFLAGS) 

ejecutar: compilar 
	./batallas

ejecutar_valgrind: compilar
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./batallas