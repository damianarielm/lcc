// gcc ejercicio1.c bitsdef.c -lgmp

#include <stdio.h> // printf
#include "bitsdef.h"

void main () {
	printf("Ejercicio 1: "); bits(1 << 31);
	printf("Ejercicio 2: "); bits((1 << 31) | (1 << 15));
	printf("Ejercicio 3: "); bits(-1 & (-1 << 8));
	printf("Ejercicio 4: "); bits(0xaa | (0xaa << 24));
	printf("Ejercicio 5: "); bits(5 << 8);
	printf("Ejercicio 6: "); bits(-1 & (~(1 << 8)));
}
