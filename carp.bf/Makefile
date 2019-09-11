CC=gcc
CFLAGS= -g -O2 -std=c99 -Wall -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Werror -o
VALGRIND= valgrind --leak-check=full --track-origins=yes --show-reachable=yes
OBJET=bf
ARCH_C=bf.c pila.c
ARCH = 01_script

all:valgrind
	
	echo
	notify-send "Compilado!" -t 1500

valgrind:compilar
	
	echo
	$(VALGRIND) ./$(OBJET) $(ARCH)

compilar:
	
	echo
	$(CC) $(ARCH_C) $(CFLAGS) $(OBJET)
	
clean:

	rm $(OBJET)