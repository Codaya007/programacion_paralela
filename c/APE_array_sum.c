/**
 *    Instrucciones:
 *   Dado un arreglo de tamaño N, dividirlo en partes iguales entre los procesos. Cada proceso calcula la suma de su segmento y utiliza MPI para obtener la suma total en el proceso raíz.
 *
 * Comandos de ejecución:
 * mpicc archivo.c -o  archivo
 * mpirun -np <n_proces> archivo
 *
 */
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    double t, t_final;
    //! Declaración e inicialización
    int rank, size, local_sum = 0, global_sum = 0;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Arreglo de 10 elementos
    int n = sizeof(arr) / sizeof(arr[0]);          // Tamaño total del array (número de elementos)

    MPI_Init(&argc, &argv);               // Inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el tamaño del comunicador
    t = MPI_Wtime();

    //! Sumas parciales
    // Calcular cuántos elementos le corresponden a cada proceso
    int n_local = n / size; // Dividimos el array en partes iguales

    int arr_local[n_local]; // Arreglo para la parte local del proceso

    // El proceso 0 reparte los segmentos del arreglo a cada proceso
    MPI_Scatter(arr, n_local, MPI_INT, arr_local, n_local, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculo una suma parcial del segmento local
    for (int i = 0; i < n_local; i++)
    {
        local_sum += arr_local[i];
    }

    printf("\nProceso %d; suma de proceso: %d\n", rank, local_sum);

    //! Sumo las porciones
    // Sumo en una sola, las sumas totales
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("La suma total es %d\n", global_sum);
    }

    t_final = MPI_Wtime();

    printf("Tiempo transcurrido: %f segundos\n", t_final - t);

    MPI_Finalize(); // Finalizo MPI
    return 0;
}
