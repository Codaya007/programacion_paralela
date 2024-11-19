#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Inicializar MPI

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  // Obtener el rango del proceso

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  // Obtener el tamaño del comunicador

    // Cada proceso calcula una suma parcial de un segmento del arreglo
    int local_sum = 0;
    for (int i = world_rank; i < 100; i += world_size) {
        local_sum += i;
    }
    printf("\nProces %d suma de proceso : %d ", world_rank, local_sum);
    int global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);  // Sumar todas las sumas parciales

    if (world_rank == 0) {
        printf("La suma total es %d\n", global_sum);
    }

    MPI_Finalize();  // Finalizar MPI
    return 0;
}

