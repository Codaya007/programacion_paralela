#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

int your_slow_code()
{
    int i;
    double tmp = 1.1;

    for (i = 1; i < 2000; i++)
    {
        tmp = (tmp + 100) / i;
    }
    return 0;
}

int main()
{
    float real_time, proc_time;
    long long flpops;
    int retval;

    // Inicializar PAPI
    if ((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT)
    {
        fprintf(stderr, "PAPI library init error!\n");
        exit(1);
    }

    // Crear un EventSet
    int EventSet = PAPI_NULL;
    if ((retval = PAPI_create_eventset(&EventSet)) != PAPI_OK)
    {
        fprintf(stderr, "Error creating event set: %s\n", PAPI_strerror(retval));
        exit(1);
    }

    // Añadir eventos al EventSet
    if ((retval = PAPI_add_event(EventSet, PAPI_FP_OPS)) != PAPI_OK)
    {
        fprintf(stderr, "Error adding PAPI_FP_OPS: %s\n", PAPI_strerror(retval));
        exit(1);
    }

    // Iniciar medición
    if ((retval = PAPI_start(EventSet)) != PAPI_OK)
    {
        fprintf(stderr, "Error starting PAPI: %s\n", PAPI_strerror(retval));
        exit(1);
    }

    // Ejecutar el código a medir
    your_slow_code();

    // Detener medición
    if ((retval = PAPI_stop(EventSet, &flpops)) != PAPI_OK)
    {
        fprintf(stderr, "Error stopping PAPI: %s\n", PAPI_strerror(retval));
        exit(1);
    }

    printf("Total floating-point operations: %lld\n", flpops);

    // Limpieza
    PAPI_shutdown();
    return 0;
}