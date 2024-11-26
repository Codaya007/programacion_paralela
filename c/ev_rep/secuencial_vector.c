#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int N, i;
    int *V, sum = 0;

    printf("\nLongitud del vector: ");
    scanf("%d", &N); // Multiplo del numero de procesos

    V = (int *)malloc(sizeof(int) * N);

    // Se inicializa el vector con números aleatorios entre -50 y 49
    for (i = 0; i < N; i++)
        V[i] = rand() % 100 - 50;

    printf("\nVector inicializado:\n");
    imprimir_vector(V, N);

    // En sum se acumula la sumatoria de los elementos del vector
    for (i = 0; i < N; i++)
        sum = sum + V[i];

    for (i = 0; i < N; i++)
        V[i] = V[i] * sum;

    // Imprimir unos resultados
    printf("\nRESULTADOS:");
    printf("\nsum = %d\n", sum);
    // printf("\n V[0] = %d, V[N/2] = %d, V[N-1] = %d\n\n\n", V[0], V[N / 2], V[N - 1]);
    printf("Vector final:\n");
    imprimir_vector(V, N);

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecución secuencial: %f seg\n", cpu_time_used);

    return 0;
}
