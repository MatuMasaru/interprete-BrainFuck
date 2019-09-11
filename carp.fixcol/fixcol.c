#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ARG_VALIDO 3





int main(int argc, char *argv[]){


	if (argc!= ARG_VALIDO){
		fprintf(stderr,"%s","Error: Cantidad erronea de parametros\n" );
		return -1;
	}

	FILE* archivo= fopen(argv[1], "r");
	if (!archivo){
		fprintf(stderr, "Error: archivo fuente inaccesible");
		return 1;
	}

	char*resto;
	long largo_columnas = strtol(argv[2], &resto, 0);
	if (*resto){
		fprintf(stderr,"El argumento \"%s\" no es un numero!\n", resto);
		return -1;
	}

	
	int caracter;
	int cont= 0;
	while((caracter = fgetc(archivo)) != EOF){

		if(caracter != '\n'){
			cont++;
			printf("%c", caracter );
		}
		
		if(caracter == '\n' || cont == largo_columnas){
			if(cont > 0 )
				printf("\n");
			cont = 0;
		}
	}
	/*while((caracter = fgetc(archivo)) != EOF){
		cont++;
		printf("%c", caracter );
		if(cont == largo_columnas || caracter == '\n'){
			if(cont == largo_columnas && caracter != '\n')
				printf("\n");
			cont=0 ;
		}
	}*/
	
	fclose(archivo);
	
	return 0;
}


