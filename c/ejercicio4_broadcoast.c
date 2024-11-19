#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
//#include "/usr/include/mpi/mpi.h"

int obtenerCount(int i, int a, int b, int n);
float obtenerResultado(int lim, int count);

int main(void){
	int i = 0, a = 0, b = 0;
	int limite, count = 0;
	int rank, size;
	float salida = 0;
	
	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0){
		limite = 10000000;
	}
	MPI_Bcast(
		&limite, 	/* Buffer*/
		1,		/* Count*/
		MPI_INT, 	/* datatype*/
		0,		/* root*/
		MPI_COMM_WORLD	/* Comunicador*/
	);
	

	count = obtenerCount(i, a, b, limite);

	salida = obtenerResultado(limite, count);
	printf("Count = %d Salida = %f proceso = %d \n",count, salida, rank);
	if (rank == 0){
		printf("La respuesta es %f \n",salida);

	}
			

	MPI_Finalize();
	return 0;
}

float obtenerResultado(int lim, int count){
	float res = (4 * ((float) count / lim));
	return res;
}

int obtenerCount(int i, int a, int b, int n){
	int count = 0;

		while (i < n){
			a = rand();
			b = rand();
			if ((a * a) + (b * b) < 1){
				count++;
			}
			i++;
		}	

	return count;
}

