#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data = 0;
    int *buf = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int arr[6] = {1,2,3,4,5,6};
        buf = arr;
    }

    printf("\nData before scatter in process %d is : %d ", rank, data);


    MPI_Scatter(buf, 1, MPI_INT, &data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    

    printf("\nData after scatter in process %d is : %d ", rank, data);
    data *= 2;
    printf("\nData after *=2 %d is : %d ", rank, data);
    
    if (rank == 4){
    		data = 100;
    	}
    
    MPI_Gather(&data, 1, MPI_INT, buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\nProceso raíz ha recolectado los resultados: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", buf[i]);
        }
        printf("\n");
 //       free(buf);
    }
    
    MPI_Finalize();

    return 0;
}
