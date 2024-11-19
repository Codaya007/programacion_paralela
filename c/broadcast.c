#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size;
    int data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        data = 100;
        printf("Proceso %d inicializa data con el valor %d", rank, size);
    }

    // Difunde el valor de data desde el proceso raíz (0) a todos los procesos
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Proceso %d recibió data con valor %d\n", rank, data);
    int newData = data + rank;
    printf("El nuevo valor es %d\n", newData);

    MPI_Finalize();
    return 0;
}