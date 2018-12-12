// gcc omp_parallel.c -fopenmp

#include <stdio.h> // printf
#include <omp.h> // pragma, omp_get_thread_num, omp_get_num_threads

void main () {
	#pragma omp parallel num_threads(20)
	{
		printf("Proceso %d. Cantidad de procesos: %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
}
