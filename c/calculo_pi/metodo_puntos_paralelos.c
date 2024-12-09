#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    //! Inicialización de MPI
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identificador de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número total de procesos

    //! Declaro las variables
    // Valores conocidos
    const float DIAMETRO = 2.0;
    float radio = DIAMETRO / 2;
    // Valores que deben ser ingresados por el usuario
    int N;
    // Valores que deben calcularse dinámicamente
    float c, angulo, angulo_radianes, perimetro_local, PI;

    //! Solicito interacción del usuario en el proceso principal (rank == 0)
    if (rank == 0)
    {
        printf("\nCon cuántos lados (N) desea calcular PI: ");
        fflush(stdout);  // Vaciar el buffer para que el mensaje aparezca inmediatamente
        scanf("%d", &N); // Múltiplo del número de procesos
    }

    // Enviar el valor de N a todos los procesos
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //! Calculos generales
    angulo = 360.0 / N;                        // Ángulo central en grados
    angulo_radianes = angulo * (M_PI / 180.0); // Convertir a radianes

    //! Mediante el Teorema de coseno calculo c: c = 2 * radio * sin(angulo / 2)
    // Calculamos la longitud de cada lado usando la fórmula directa con el seno
    c = 2 * radio * sin(angulo_radianes / 2);

    // Dividir el trabajo entre los procesos (cálculo del perímetro)
    int local_N = N / size;                             // Número de lados que procesa cada proceso
    int start = rank * local_N;                         // Índice de inicio para cada proceso
    int end = (rank == size - 1) ? N : start + local_N; // Índice final (el último proceso toma los restos)

    // Cada proceso calcula su parte del perímetro
    perimetro_local = 0.0;
    for (int i = start; i < end; i++)
    {
        perimetro_local += c;
    }

    // Sumar los resultados locales en el proceso 0
    MPI_Reduce(&perimetro_local, &PI, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    //! Resultados
    if (rank == 0)
    {
        PI = PI / DIAMETRO; // Aproximación de PI

        printf("\n\nRESULTADOS OBTENIDOS:\n");
        printf("N: %d\n", N);
        printf("Radio: %.2f\n", radio);
        printf("Ángulo A: %.2f grados\n", angulo);
        printf("Longitud del lado a y b: %.2f\n", radio);
        printf("Longitud del lado c: %.2f\n", c);
        printf("Perímetro: %.5f\n", PI);
        printf("Aproximación de PI: %.5f\n", PI);
    }

    //! Finalización de MPI
    MPI_Finalize();
    return 0;
}
