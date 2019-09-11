#define _GNU_SOURCE

#include "pila.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define ARGUMENTOS_VALIDOS 2
#define TAM_BASE_VEC 100
#define AVANZAR_PTR 62			//representa al '>'
#define RETROCEDER_PTR 60		//representa al '<'
#define IMPRIMIR 46				//representa al '.'
#define INGRESAR_CHAR 44		//representa al ','
#define RESTAR_1_CONTENIDO 45	//representa al '-'
#define SUMAR_1_CONTENIDO 43	//representa al '+'
#define INICIO_CICLO 91			//representa al '['	
#define FINAL_CICLO 93			//representa al ']'
#define INDICE_REDIMENCION 2
#define POSICION_REDIMENCION 10
/*estructura del brainfuck
*/
typedef struct bf {
	size_t tamanio_vector;
	unsigned char* vector ;
	int posicion_vector;
	pila_t* pila_ciclos;
}brainfuck_t;
/*crea una estructura del brainfuck
*post: devuelve todos los campos de la structura inicializados en cero o vacios, si no se puede crear, devuelve NULL.
*/
brainfuck_t* bf_crear(){

	brainfuck_t* bf = malloc(sizeof(brainfuck_t));
	if (!bf)
		return NULL;
	bf->vector = calloc( TAM_BASE_VEC , sizeof(char) );
	if (!bf->vector){
		free(bf);
		return NULL;
	}
	bf->pila_ciclos = pila_crear();
	if (!bf->pila_ciclos){
		free(bf->vector);
		free(bf);
		return NULL;
	}
	bf->tamanio_vector = TAM_BASE_VEC;
	bf->posicion_vector = 0;
	return bf;
}

/*pre:el brainfuck fue creado.
*post:inicializa desdel el tamanio anterior hasta el nuevo , asignando el cero.
*/
void inicializar_nuevo_tam(brainfuck_t* bf , size_t tamanio_nuevo,unsigned char * vector){
	for (size_t i = (bf->posicion_vector +1 ); i <tamanio_nuevo; ++i)
		vector[i] = 0;
}


/*pre:El brainfuck fue creado.
*post:redimenciona el vector inicializando la nueva memoria en 0.
*/
unsigned char* redimencionar_vector(brainfuck_t* bf , size_t tamanio_nuevo){

	unsigned char* nuevo_vector= realloc(bf->vector, tamanio_nuevo);
	if (!nuevo_vector)
		return NULL;
	inicializar_nuevo_tam( bf , tamanio_nuevo, nuevo_vector);
	bf->tamanio_vector = tamanio_nuevo; 
	return nuevo_vector ;
}
/*pre:El brainfuck fue creado.
*post: se apilo la posicion donde se encontro un inicio de ciclo
*
*/

void inicia_ciclo( brainfuck_t* bf , int  *pos_ptr ){
	int *valor = malloc(sizeof(int));
	*valor = *pos_ptr;
	pila_apilar( bf->pila_ciclos , valor );
}
/*pre:archivo fue abierto correctamende. El brainfuck fue creado.
*post: posiciona al lector del archivo luego del cierre del ciclo.
*/
void saltear_ciclo(brainfuck_t* bf , FILE * archivo , int *pos_ptr ){
	size_t cont = 1;

	while( cont != 0 && !feof(archivo) ) {
		int caracter_leido = fgetc(archivo);
		if ( caracter_leido == INICIO_CICLO )
			cont++;
		else if (  caracter_leido == FINAL_CICLO )
			cont--;
		(*pos_ptr)++;
	}
}

/*pre:archivo fue abierto correctamende. El brainfuck fue creado.
*post: vuelve al principio del ciclo de lectura del archivo. si no se puede imprimer un error.
*/
void ir_principio_ciclo(brainfuck_t* bf, FILE* archivo, int *pos_ptr){
	if (!pila_esta_vacia(bf->pila_ciclos)){
  		int* aux = pila_ver_tope(bf->pila_ciclos);


		fseek(archivo, (long) *aux -*pos_ptr , SEEK_CUR);
		*pos_ptr = *aux ;
	}else
		fprintf(stderr, "%s","!!MAL, NO SE PUEDE VOLVER POR QUE NO SE ABRIO!!!" );
}

/*pre:archivo fue abierto correctamende. El brainfuck fue creado.
*post:ejecuta la accion enviada por parametro.
*/
void accion_a_realizar(brainfuck_t* bf,  int accion, FILE * archivo ,int  *pos_ptr ){
	switch(accion){
		case SUMAR_1_CONTENIDO:
		
			(bf->vector[bf->posicion_vector]++);

		break;

		case RESTAR_1_CONTENIDO:

			(bf->vector[bf->posicion_vector])--;
		break;

		case AVANZAR_PTR:
			bf->posicion_vector++;
		break;

		case RETROCEDER_PTR:

			if (bf->posicion_vector)
				bf->posicion_vector--;

		break;

		case IMPRIMIR:

			printf("%c",bf->vector[bf->posicion_vector] );
		break;
		case INGRESAR_CHAR :

			bf->vector[bf->posicion_vector]= (unsigned char )getchar();
		break;
		case INICIO_CICLO:

			if (bf->vector[bf->posicion_vector])
				inicia_ciclo(bf, pos_ptr);
			else
				saltear_ciclo(bf, archivo, pos_ptr);
		break;
  		
  		case FINAL_CICLO:

			if(bf->vector[bf->posicion_vector])
				ir_principio_ciclo(bf, archivo, pos_ptr);
			else
				free(pila_desapilar(bf->pila_ciclos));
		break;
  		
	}	
}

/*pre:brainfuck fue creado.
*destruye todos los campos del brainfuck.
*/
void brainfuck_destruir(brainfuck_t * bf){
	pila_destruir(bf->pila_ciclos);
	free(bf->vector);
	free(bf);
}
/*pre:archivo fue abierto correctamende. El brainfuck fue creado.
*post:se ejecutaron todos  los comandos del archivo.
*/
void lectura_comandos(brainfuck_t* bf, FILE * archivo){
	int caracter;
	int posicion_ptr= 0;
	while(  ( caracter = fgetc(archivo) ) != EOF){
		posicion_ptr++;
		accion_a_realizar( bf , caracter, archivo, &posicion_ptr);

		if(bf->posicion_vector > (bf->tamanio_vector -POSICION_REDIMENCION) )
			redimencionar_vector(bf , bf->tamanio_vector *INDICE_REDIMENCION);
	}
}	
/*pre:el archivo fue abierto correctamente
*interpreto todos los comandos del archivo.
*/
void inicio_brainfuck(FILE *archivo){

	brainfuck_t* bf = bf_crear();
	if(!bf)
		return; 
	lectura_comandos(bf , archivo);
	brainfuck_destruir(bf);
}

int main(int argc, char const *argv[]){
	// aca valido la cantidad de argumentos y segun sean, solicito nombre por stdiin
	FILE* archivo ;

	if (argc == ARGUMENTOS_VALIDOS){
		archivo = fopen( argv[1] , "r");
	}else{
		fprintf(stderr,"%s","!! Error: Cantidad erronea de parametros\n" );
		return -1;
	}
	if (!archivo){
		fprintf(stderr, "Error: archivo fuente  %s inaccesible\n", argv[1]);
		return -1;
	}
	
	inicio_brainfuck(archivo);
	
	if(argc == ARGUMENTOS_VALIDOS){
		fclose(archivo);
	}

	return 0;
}