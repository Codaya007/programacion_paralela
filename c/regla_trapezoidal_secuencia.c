#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

// Definición de la función a integrar, por ejemplo, f(x) = x^2
double f(double x)
{
    // return pow(x, 3);
    return x * x * x;
}

// Función que calcula el área bajo la curva usando la regla del trapecio
int main(int argc, char **argv)
{
    int i = 0;
    double a = 0.0;
    double b = 10.0;
    double n = 2 000 000 000.0;
    double suma = 0.0;
    double w = (b - a) / n;

    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    double x_i;
    if (world_rank == 0)
    {
        for (i = 1; i < n; i++)
        {
            x_i = a + i * w;
            suma = suma + (f(x_i));
        }
    }
    double total = w * (((f(a) + f(b)) / 2) + suma);
    printf("Valor aproximado de la integral es: %f\n", total);

    MPI_Finalize();
}
