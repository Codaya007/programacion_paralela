#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char **argv)
{
    //! Declaro las variables
    // Valores conocidos
    const float DIAMETRO = 2.0;
    float radio = DIAMETRO / 2;
    // Valores que deben ser ingresados por el usuario
    int N;
    // Valores que deben calcularse dinámicamente
    float c, angulo, angulo_radianes, perimetro, PI;

    //! Solicito interacción del usuario
    printf("\nCon cuántos lados (N) desea calcular PI: ");
    fflush(stdout);  // Vaciar el buffer para que el mensaje aparezca inmediatamente
    scanf("%d", &N); // Múltiplo del número de procesos

    //! Calculos generales
    angulo = 360.0 / N;                        // Ángulo central en grados
    angulo_radianes = angulo * (M_PI / 180.0); // Convertir a radianes

    //! Mediante el Teorema de coseno calculo c: c = 2 * radio * sin(angulo / 2)
    // Calculamos la longitud de cada lado usando la fórmula directa con el seno
    c = 2 * radio * sin(angulo_radianes / 2);

    perimetro = c * N; // Perímetro del polígono inscrito

    PI = perimetro / DIAMETRO; // Aproximación de PI

    //! Resultados
    printf("\n\nRESULTADOS OBTENIDOS:\n");
    printf("N: %d\n", N);
    printf("Radio: %.2f\n", radio);
    printf("Ángulo A: %.2f grados\n", angulo);
    printf("Longitud del lado a y b: %.2f\n", radio);
    printf("Longitud del lado c: %.2f\n", c);
    printf("Perímetro: %.5f\n", perimetro);
    printf("Aproximación de PI: %.5f\n", PI);

    return 0;
}
