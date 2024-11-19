#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3 // Tamaño de la matriz (3x3)

void gauss_jordan(int rank, int size, double matrix[N][N + 1])
{
    int i, j, k;
    double temp;

    // Realización de eliminación de Gauss-Jordan
    for (i = 0; i < N; i++)
    {
        // Paso 1: hacer la diagonal de la matriz igual a 1
        if (rank == i % size)
        { // Solo el proceso que maneja la fila i
            temp = matrix[i][i];
            for (j = 0; j < N + 1; j++)
            {
                matrix[i][j] /= temp;
            }
        }
        MPI_Barrier(MPI_COMM_WORLD); // Sincronización entre procesos

        // Paso 2: hacer ceros en la columna de la fila i
        for (j = 0; j < N; j++)
        {
            if (rank == j % size && j != i)
            { // Solo el proceso que maneja la fila j
                temp = matrix[j][i];
                for (k = 0; k < N + 1; k++)
                {
                    matrix[j][k] -= temp * matrix[i][k];
                }
            }
        }
        MPI_Barrier(MPI_COMM_WORLD); // Sincronización entre procesos
    }
}

int main(int argc, char **argv)
{
    int rank, size;
    double matrix[N][N + 1] = {
        {1, 3, -1, 6},
        {2, -1, 3, 3},
        {3, 2, 4, 11}};

    MPI_Init(&argc, &argv);               // Inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el tamaño del comunicador

    // Realizar la eliminación de Gauss-Jordan en paralelo
    gauss_jordan(rank, size, matrix);

    // El proceso 0 imprime los resultados
    if (rank == 0)
    {
        printf("La matriz final es:\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N + 1; j++)
            {
                printf("%.2f ", matrix[i][j]);
            }
            printf("\n");
        }

        // Imprimir las soluciones (última columna)
        printf("Las soluciones son: ");
        for (int i = 0; i < N; i++)
        {
            printf("%.2f ", matrix[i][N]);
        }
        printf("\n");
    }

    MPI_Finalize(); // Finalizo MPI
    return 0;
}
