#include <stdio.h>

// Definición de la función a integrar, por ejemplo, f(x) = x^2
double f(double x)
{
    return x * x * x;
}

// Función que calcula el área bajo la curva usando la regla del trapecio
double trapezoidal(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

int main()
{
    double a = 0.0;
    double b = 10.0;
    int n = 2000000000.0;

    double area = trapezoidal(a, b, n);
    printf("El área bajo la curva es: %lf\n", area);

    return 0;
}
