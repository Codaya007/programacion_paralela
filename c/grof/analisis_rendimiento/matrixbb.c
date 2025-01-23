#include <stdlib.h>
#include <stdio.h>
 
 
#define MAX_MSIZE 10000
#define MSIZE     1000
 
float **allocate(int size){
	int i;
	float **m;
	m = malloc(sizeof(float *) * size);
	m[0] = malloc(sizeof(float) * size * size);
	for (i = 1; i < size; i++)
		m[i] = m[i - 1] + size;
	return m;
}

void initialize(float **a, float **b, int size)
{
  int i, j;
  
  for (i = 0; i < size; i++) {
    for (j = 0 ; j < size; j++) {
      a[i][j] = (float) rand() / RAND_MAX ;
      b[i][j] = (float) rand() / RAND_MAX ;
      //~ a[i][j] = 1;
      //~ b[i][j] = 1;
    }
  }
}

float **transpose(float **matrix, int size)
{
	float **trans;
	int i, j;
	trans = allocate(size);
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			trans[j][i] = matrix[i][j];
	return trans;
}
 
float **multiply(float **a, float **b, int size)
{
	int i, j, k;
	float sum = 0.0;
	float **c, **trans;
	c = allocate(size);
	trans = transpose(b, size);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			sum = 0.0;
			for (k = 0; k < size; k++) 
				sum = sum + (a[i][k] * trans[j][k]);
			
			c[i][j] = sum;
		}
	}
	free(trans[0]); free(trans);
	return c;
}
 
int main(int argc, char* argv[])
{
	int size = MSIZE ;
	 
	float **a;
	float **b;
	float **c;
	if (argc > 1)
		size = atoi(argv[1]);

	printf("Running program with size: %d...\n", size);	
	a = allocate(size);
	b = allocate(size);
	initialize(a, b, size);
	c = multiply(a, b, size);

	printf("c[0][0] = %f\n", c[0][0]);
	
	free(a[0]); free(b[0]); free(c[0]);
	free(a); free(b); free(c);
	return( 0) ;
}
