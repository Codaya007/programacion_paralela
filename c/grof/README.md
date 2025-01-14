# Compilación del código

gcc ejemplo1.c -o ejemplo1 -lm -pg

./ejemplo1 10

gprof -b calva gmon.out > calvareporte

# Para ver el tiempo por métodos

gprof mi_programa gmon.out

# Gcov permite ver la cantidad de veces que se ejecuta por línea

gcc -fprofile-arcs -ftest-coverage ejemplo1.c -o ejemplo1 -lm
./ejemplo1 1000
gcov calva
less ejemplo1.c.gcov
