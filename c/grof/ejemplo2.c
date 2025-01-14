#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    double *A, total;
    int i, j, k, N;

    N = atoi(argv[1]);
    A = (double *) malloc (sizeof(double) * N * N);

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            A[i * N  + j] = 1;
    }

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            total = 0;
            for (k = j; k < N; k++)
                  total += A[j * N + k];
            A[i * N + j] = total;
        }
    }
	free(A);
    return 0;
}



