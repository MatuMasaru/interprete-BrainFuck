#include "pila.h"
#include<stdio.h>
#include <stdlib.h>
#define DATOS_INICIAL 1
#define CAPACIDAD_INICIAL 1
#define CANTIDAD_INICIAL 0
#define INDICE_DECRECIMIENTO 4
#define INDICE_REDIMENCION 2
/* Definición del struct pila proporcionado por la cátedra.
 */

struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.tope
    size_t capacidad;  // Capacidad del arreglo 'datos'. 
};

/*pre:pila debe estar creada
*	post:pedira mas memoria para la pila, devolvera TRUE si pudo o FALSE, en caso contrario
	y actualizara las variables correspondientes. 
 */
bool redimensionar_pila(pila_t *pila,size_t nueva_capacidad ){

	void*datos_nuevos=realloc(pila->datos, (nueva_capacidad * sizeof(void*))  );
	if (datos_nuevos== NULL)
		return false;

	pila->datos=datos_nuevos;
	pila->capacidad=nueva_capacidad;
	return true;
}
/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
pila_t* pila_crear(void){
	pila_t* pila=malloc(sizeof(pila_t));
	if (!pila) 
        return NULL;
   
    pila->datos=malloc(DATOS_INICIAL* sizeof(void*));
      if (!pila->datos) {
      	free(pila);
        return NULL;
    }
    pila->cantidad= CANTIDAD_INICIAL;
    pila->capacidad=DATOS_INICIAL;
   return pila;
}
void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}
bool pila_esta_vacia( const pila_t *pila){
	return (!pila->cantidad);
}
bool pila_apilar(pila_t *pila, void* valor){
	bool redimenciona=true;
	if (pila->cantidad ==pila->capacidad){
		redimenciona=redimensionar_pila(pila, pila->capacidad*INDICE_REDIMENCION);
	}
	if (redimenciona){
		pila->datos[pila->cantidad]=valor;
		pila->cantidad++;		
	}
	return redimenciona;
}

void* pila_ver_tope( const pila_t *pila){
	if (!pila->cantidad)
		return NULL;
	return pila-> datos[pila->cantidad-1];
}


void* pila_desapilar(pila_t *pila){
	void* desapilado=NULL;
	if (pila->cantidad){
		desapilado =pila->datos[pila->cantidad-1];
		pila->cantidad--;
		if (pila->cantidad== pila->capacidad/INDICE_DECRECIMIENTO && pila->capacidad != CAPACIDAD_INICIAL){
			redimensionar_pila(pila, pila->capacidad/INDICE_REDIMENCION);
		}
		return desapilado;
	}
	return NULL;
}