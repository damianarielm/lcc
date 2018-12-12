// gcc omp_sections.c -fopenmp

#include <stdio.h> // printf
#include <omp.h> // pragma, omp_get_thread_num

void main () {
	#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section
		printf("Proceso %d trabajando.\n", omp_get_thread_num());
		#pragma omp section
		printf("Proceso %d trabajando.\n", omp_get_thread_num());
		#pragma omp section
		printf("Proceso %d trabajando.\n", omp_get_thread_num());
	}
}
