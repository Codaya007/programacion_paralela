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

// Función que calcula el área del trapecio en un tramo
double funcionTrapezoidalTramo(double a, double b, double h)
{
    double suma = 0.0;

    for (double i = a; i <= b; i += h)
    {
        printf("Valor de i tramo %i a %i: %i\n", a, b, i);

        suma += f(i);
    }

    double total = h * (((f(a) + f(b)) / 2) + suma);

    return total;
}

// Función que calcula el área bajo la curva usando la regla del trapecio
int main(int argc, char **argv)
{
    int i = 0;
    double a = 0.0;
    double b = 10.0;
    double n = 2000000000.0;
    double h = (b - a) / n;
    double local_suma = 0.0;
    double total_suma = 0.0;

    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double local_n = n / size;

    printf("local_n = %.2f; n = %i; size = %i; world_rank = %i \n", local_n, n, size, world_rank);

    double local_a = a + (world_rank * h);
    double local_b = local_a + local_n;

    local_suma = funcionTrapezoidalTramo(local_a, local_b, h);

    printf("Proceso %i: a = %i; b = %i; suma = %.2f\n", world_rank, local_a, local_b, local_suma);

    if (world_rank == 0)
    {
        // Si es el proceso 0, sumo los valores totales
        for (size_t i = 0; i < size; i++)
        {
            printf("Recolectando de proceso %i: suma_local = %.2f; suma_total = %.2f\n", local_suma, total_suma);

            MPI_Recv(&local_suma, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_suma += local_suma;
        }
    }
    else
    {
        // Si NO es el proceso 0, envío la suma local
        MPI_Send(&local_suma, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    printf("Valor aproximado de la integral es: %.5f\n", total_suma);

    MPI_Finalize();
}
