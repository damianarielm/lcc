// gcc ejercicio6.c ejercicio6.s

#include <stdio.h>
#include <malloc.h>

int solve(float a, float b, float c, float d, float e, float f, float* x, float* y);

void main() {
	float a, b, c, d, e, f;
	float* x = malloc(sizeof(float));
	float* y = malloc(sizeof(float));

	printf("ax + by = c\ndx + ey = f\n"); puts("");

	printf("Ingrese el coeficiente a: "); scanf("%f", &a);
	printf("Ingrese el coeficiente b: "); scanf("%f", &b);
	printf("Ingrese el coeficiente c: "); scanf("%f", &c);
	printf("Ingrese el coeficiente d: "); scanf("%f", &d);
	printf("Ingrese el coeficiente e: "); scanf("%f", &e);
	printf("Ingrese el coeficiente f: "); scanf("%f", &f);

	puts("");

	if (!solve(a, b, c, d, e, f, x, y)) {
		printf("X: %f\nY: %f\n", *x, *y);
	} else {
		printf("Sistema incompatible/indeterminado\n");
	}

	free(x);
	free(y);
}
