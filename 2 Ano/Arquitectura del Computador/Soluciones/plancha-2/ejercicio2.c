// gcc ejercicio2.c

#include <stdio.h> // printf
#include <math.h> // isnan
#include "floatdefs.h" // exponente, mantisa

int myisnan(float f) {
    return ((exponente(f) == (1 <<8)-1) && mantisa(f));
}

int myisnan2(float f) {
    return *((unsigned long*) &f) > 2139095040;
}

void main() {
	float nan = 0.0 / 0.0;
	float inf = 1.0 / 0.0;

	printf("isnan(0.0 / 0.0): %d\n", isnan(nan));
	printf("myisnan(0.0 / 0.0): %d\n", myisnan(nan));
	printf("myisnan2(0.0 / 0.0): %d\n", myisnan2(nan));

	printf("\n1.0 / 0.0 == INFINITY: %d\n", inf == INFINITY);
	printf("NAN == INFINITY: %d\n", nan == INFINITY);
	printf("1.0 + INFINITY: %f\n", 1.0 + INFINITY);
}
