#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data;

    // Inicializar MPI
    MPI_Init(&argc, &argv);

    // Obtener el rango del proceso
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el tamaño del comunicador
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Si soy el proceso raíz (por ejemplo, el proceso con rank 0)
    if (rank == 0) {
        data = 100;  // El valor que vamos a transmitir
        printf("Proceso %d transmitiendo dato: %d\n", rank, data);
    }

    // Sincronización de todos los procesos antes de la transmisión
    MPI_Barrier(MPI_COMM_WORLD);

    // Transmitir el valor desde el proceso raíz a todos los demás
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Sincronización de todos los procesos después de la transmisión
    MPI_Barrier(MPI_COMM_WORLD);

    // Cada proceso imprime el valor recibido
    printf("Proceso %d recibió el dato: %d\n", rank, data);

    // Finalizar MPI
    MPI_Finalize();

    return 0;
}
