// gcc ejercicio7.c ejercicio7.s

#include <stdio.h>

void sum(float* a, float* b, int len);

void main() {
	int len;
	printf("Ingrese cantidad de flotantes: ");
	scanf("%d", &len);
	puts("");

	float a[len];
	float b[len];

	for (int i = 0; i < len; i++) {
		printf("Ingrese el flotante a[%d]: ", i);
		scanf("%f", &a[i]);
		printf("Ingrese el flotante b[%d]: ", i);
		scanf("%f", &b[i]);
	}
	puts("");

	sum(a, b, len);

	for (int i = 0; i < len; i++) {
		printf("a[%d] + b[%d] = %f\n", i, i, a[i]);
	}
}
