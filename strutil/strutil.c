#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define PRUEBA 13
#define TAMANIO_MINIMO 9

/*
 * Devuelve una nueva cadena con los primeros ‘n’ caracteres de la cadena
 * ‘str’. La liberación de la memoria dinámica devuelta queda a cargo de
 * quien llame a esta función.
 *
 * Devuelve NULL si no se pudo reservar suficiente memoria.
 */

char *substr(const char *str, size_t n){
	
	size_t largo = strlen(str);
	size_t tamanio = largo <= n ?  largo : n ;

	char* nueva_cadena = malloc((tamanio + 1) * sizeof(char));
	if(!nueva_cadena)
		return NULL;
	strncpy(nueva_cadena, str, tamanio );
	nueva_cadena[tamanio]='\0';
	return nueva_cadena;
}


char **split(const char *str, char sep){

	int cant_string = 0;
	size_t largo_str = strlen(str);
	for ( int i= 0 ; i <= largo_str ; ++i){
		if(str[i] == sep || str[i]=='\0')
		cant_string++;
	}
	char** arreglo = malloc(sizeof(char*) * (cant_string + 1) );
	if (!arreglo){
		return NULL;
	}

	size_t separador_anterior = 0;
	size_t cant_letras = 0;
	size_t pos_arreglo = 0;

	for (size_t contador= 0; contador <= largo_str  ; contador++){

		if(str[contador] == sep || str[contador] == '\0' ){
			arreglo[pos_arreglo] = substr( str + separador_anterior, cant_letras);
			pos_arreglo++ ;
			cant_letras = 0;
			separador_anterior = contador + 1 ; 
		}else 
			cant_letras ++;
	}

	arreglo[pos_arreglo ] = NULL;
	
	return arreglo;

}

size_t largo_todos(char** strv ){
	size_t largo=0;
	size_t contador = 0;
	while(strv[contador]){
		largo+=strlen(strv[contador]);
		if (strv[contador+1]){
			largo++;
		}
		contador++;
	}
	return largo;

}



char *join(char **strv, char sep){
	size_t largo = largo_todos(strv);
	char* vector = malloc((largo + 1)  * sizeof(char));
	if (!vector){
		return NULL;
	}
	int pos_vector = 0;
	for (size_t i = 0; strv[i]; i++){
		for (int j = 0;  strv[i][j] != '\0' ; ++j){
			vector[pos_vector] = strv[i][j] ;
			pos_vector++;
		}
		if(strv[i+1] && sep!='\0'){
			vector[pos_vector] = sep ;
			pos_vector++;
		}
	}
	vector[pos_vector] = '\0' ;
	
	return vector;
}

void free_strv(char *strv[]){
	if(!strv)
		return ;
	size_t i = 0;
	for (; strv[i] ; ++i){
		free(strv[i]);
	}
	free(strv);

}
