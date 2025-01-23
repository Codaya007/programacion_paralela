#include <stdio.h>
#include "papi.h"
#include <stdlib.h>


int your_slow_code()
{
  int i;
  double  tmp=1.1;

  for(i=1; i<2000; i++)
  { 
    tmp=(tmp+100)/i;
  }
  return 0;
}

int main(int argc, char *argv[]){ 
	int retval;
	int Events[2] = { PAPI_TOT_INS, PAPI_TOT_CYC};
    long long values[2];

	if((retval=PAPI_start_counters(Events, 2)) < PAPI_OK)
	{ 
	printf("Could not initialise PAPI_start_counters\n");
	printf("Your platform may not support these events.\n"); 
	printf("retval: %d\n", retval);
	exit(1);
	}

	your_slow_code();


	if((retval=PAPI_stop_counters(values, 2))<PAPI_OK)
	{    
	printf("retval: %d\n", retval);
	exit(1);
	}


	printf("%lld \t PAPI_TOT_INS \n%lld \t PAPI_TOT_CYC \t \
		    %.2f insn per cycle\n", values[0], values[1], 
		                            (float) values[0] / values[1]);
	return 0;
}


