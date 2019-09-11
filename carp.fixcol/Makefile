CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
OBJET = pruebas
ARG = documento 1
ARCH_C = fixcol.c 
#ARCH_P = pruebas_strutil.c strutil.c
RAM :compilar
	./$(OBJET) $(ARG) 


all:valgrind
	
	echo
	notify-send "Compilado!" -t 1500

valgrind:compilar
	
	echo
	$(VALGRIND) ./$(OBJET) $(ARG)
PRUEBAS:
	$(CC) $(ARCH_C) $(CFLAGS) $(OBJET)
	$(VALGRIND) ./$(OBJET)

compilar:
	
	echo
	$(CC) $(ARCH_C) $(CFLAGS) $(OBJET)
	
clean:

	rm $(OBJET)
