#include "omp_check.h"
#include <stdio.h>
#include <omp.h>

void parallel_print()
{
	printf("Single thread!\n");

	#pragma omp parallel
	{
		printf("Running on multiple threads.\n");
	}
}