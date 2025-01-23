# Compilación del código

```
gcc ejemplo1.c -o ejemplo1 -lm -pg

./ejemplo1 10

gprof -b calva gmon.out > calvareporte
```

# Para ver el tiempo por métodos

```
gprof mi_programa gmon.out
```

# Gcov permite ver la cantidad de veces que se ejecuta por línea

```
gcc -fprofile-arcs -ftest-coverage ejemplo1.c -o ejemplo1 -lm
./ejemplo1 1000
gcov calva
less ejemplo1.c.gcov
```

# PERF

```
perf stat ./ejemplo2 500
```

- Con -e podemos elegir qué eventos mirar

```
perf stat -e cycles,stalled-cycles-frontend,instructions ./ejemplo2 1000
```

## ¿Qué son los frontend Cycles Idle?

Son ciclos del procesador en los que el frontend (la parte del procesador que se encarga de la decodificación de instrucciones y el manejo de la cola de instrucciones) está inactivo, es decir, no está procesando ninguna instrucción.

### Frontend

Parte encargada de traer y preparar las instrucciones para ejecutar

### Backend

Parte encargada de ejecutar instrucciones y realizar operaciones de datos

```
gcc -g -o ejemplo2 ejemplo2.c
```

```
perf stat -e duration_time,user_time,system_time,cycles ./ejemplo2 1000
```

Podemos visualizar el reporte generado en perf.data con el comando:

```
 perf report -i perf.data
```

perf stat -e duration_time,user_time,system_time,cycles,cpu-clock,task-clock ./ejemplo2 1000
