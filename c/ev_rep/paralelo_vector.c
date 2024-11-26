#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void imprimir_vector(int *V, int N)
{
    printf("[");
    for (int i = 0; i < N; i++)
    {
        printf("%d", V[i]);
        if (i < N - 1)
            printf(", ");
    }
    printf("]\n");
}

int main(int argc, char **argv)
{
    //    clock_t start, end;
    //  double cpu_time_used;

    // start = clock();

    // Variables globales
    int N, i;
    int *V, sum = 0;
    // Variables locales
    int sum_local = 0, N_local; //, V_local;
                                //! PARTE PARALELA
    // Variables MPI
    int rank, size;
    int data;

    MPI_Init(&argc, &argv);               // Inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el tamaño del comunicador

    // printf("Proceso %d\n", rank);

    if (rank == 0)
    {
        printf("\nLongitud del vector: ");
        fflush(stdout);  // Vaciar el buffer para que el mensaje aparezca inmediatamen
        scanf("%d", &N); // Multiplo del numero de procesos

        V = (int *)malloc(sizeof(int) * N);

        // Se inicializa el vector con números aleatorios entre -50 y 49
        for (int i = 0; i < N; i++)
            V[i] = rand() % 100 - 50;

        printf("\nVector inicializado:\n");
        imprimir_vector(V, N);
    }

    // Envío el tamaño del vector a todos los procesos
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    N_local = N / size;
    int V_local[N_local];

    // Se reparte el array a los procesos
    MPI_Scatter(V, N_local, MPI_INT, V_local, N_local, MPI_INT, 0, MPI_COMM_WORLD);

    // En sum se acumula la sumatoria de los elementos del vector
    for (int i = 0; i < N_local; i++)
        sum_local = sum_local + V_local[i];

    // Se reune las sumas locales en una sola: suma global
    MPI_Reduce(&sum_local, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Se reparte la suma global calculada a todos los procesos
    MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Localmente, se modifica la parte del vector en cada proceso
    for (int i = 0; i < N_local; i++)
        V_local[i] *= sum;

    // Se unen los pedazos del vector en una sola
    MPI_Gather(V_local, N_local, MPI_INT, V, N_local, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprimir unos resultados
    if (rank == 0)
    {
        printf("\nRESULTADOS:");
        printf("\nsum = %d\n", sum);
        printf("Vector final:\n");
        imprimir_vector(V, N);

        // end = clock();

        //       cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        //     printf("Tiempo de ejecución secuencial: %f seg\n", cpu_time_used);
    }

    MPI_Finalize();
    return 0;
}
