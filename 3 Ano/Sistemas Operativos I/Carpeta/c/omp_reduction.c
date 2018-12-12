// gcc omp_reduction.c -fopenmp
#include <stdio.h> // printf
#include <omp.h> // pragma

void main () {
	int i, total = 0, a[100];

	// Inicializa el arreglo
	for (i = 0; i < 100; i++) a[i] = i+1;

	#pragma omp parallel for reduction(+: total)
	for (i = 0; i < 100; i++) total += a[i];

	printf("Total: %d\n", total);
}
