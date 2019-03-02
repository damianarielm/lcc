// gcc ejercicio1.c

#include <stdio.h> // printf, scanf
#include <ieee754.h> // union ieee754_float
#include "floatdefs.h" // signo, mantisa, exponente

void main () {
	float f;
	union ieee754_float u;

	printf("Ingrese un float: "); scanf("%f", &f);
	u.f = f;

	printf("\nSigno (ieee754.h): %d\n", u.ieee.negative);
	printf("Signo (macro): %d\n", signo(f));

	printf("\nMantisa (ieee754.h): %d\n", u.ieee.mantissa);
	printf("Mantisa (macro): %d\n", mantisa(f));

	printf("\nExponente (ieee754.h): %d\n", u.ieee.exponent);
	printf("Exponente (macro): %d\n", exponente(f));
}
