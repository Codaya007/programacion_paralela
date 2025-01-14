#include <stdio.h>
#include "math.h"

#define N 50000

void sub1(int, double [], double *);
void sub2(int, double [], double *);
double myPow(double, double);

int main(){
	double sum1, sum2;
	int i, j;
	double x[N];
	for (i = 0; i < N; i++)
		x[i] = 1.234;
		
	for (j = 0; j < 1000; j++){
		sub1(N, x, &sum1);
		sub2(N, x, &sum2);
	}
	printf("sum1: %f, sum2: %f\n", sum1, sum2);

	return 0;
}



void sub1(int n, double x[], double *sum){
	int i;
	*sum = 0.; 
	for (i = 0; i < n; i++)
		*sum += 2. * myPow(x[i] + (x[i] - 1), 2) + 3. 
		     + i * 1. - 20 - 4. * myPow(i - 200, 2);
}

void sub2(int n, double x[], double *sum){
	int i;
	*sum = 0.;
	for (i = 0; i < n; i++)
		*sum += myPow(x[i], .3333333333);
}


double myPow(double x, double y){
	return pow(x, y);
}
