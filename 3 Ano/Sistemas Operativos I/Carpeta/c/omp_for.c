// gcc omp_for.c -fopmenmp

#include <stdio.h> // printf
#include <omp.h> // pragma, omp_get_thread_num

void main () {
	int i;

	#pragma omp parallel for
	for (i = 0; i < 30; i++) {
		printf("Proceso %d: i=%d\n", omp_get_thread_num(), i);
	}
}
