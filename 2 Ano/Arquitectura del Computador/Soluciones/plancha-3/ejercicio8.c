// gcc ejercicio8.c ejercicio7.s ejercicio8.s

#include <stdio.h>
#include <malloc.h>
#include <time.h>

void sum(float* a, float* b, int len);
void sum_sse(float* a, float* b, int len);

void main() {
	int len;
	printf("Ingrese cantidad de elementos: ");
	scanf("%d", &len);
	len *= 4;
	puts("");

	float* a = malloc(sizeof(float)*len);
	float* b = malloc(sizeof(float)*len);
	double t1, t2;

	clock_t begin = clock();
	sum(a, b, len);
	clock_t end = clock();
	t1 = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("La funcion sum demoro: %fs\n", t1);

	begin = clock();
	sum_sse(a, b, len);
	end = clock();
	t2 = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("La funcion sum_sse demoro: %fs\n", t2);
	puts("");

	printf("Diferencia: %fs\n", t1 - t2);

	free(a);
	free(b);
}
