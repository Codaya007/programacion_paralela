#include <stdio.h>
#include "papi.h"


int main(int argc, char *argv[]){ 
	int retval;

	if((retval=PAPI_XXXX(&arg0, &arg1, ..., &argN)) < PAPI_OK)
	{ 
	printf("Could not initialise PAPI_XXXX\n");
	printf("Your platform may not support XXXX event.\n"); 
	printf("retval: %d\n", retval);
	exit(1);
	}

	// FRAGMENTO DE CÓDIGO DE LA APLICACIÓN A MEDIR


	if((retval=PAPI_XXXX(&arg0, &arg1, ..., &argN))<PAPI_OK)
	{    
	printf("retval: %d\n", retval);
	exit(1);
	}


	printf("arg0: %f arg1: %f ... argN: %f\n", arg0, arg1,..., argN);

	return 0;
}


