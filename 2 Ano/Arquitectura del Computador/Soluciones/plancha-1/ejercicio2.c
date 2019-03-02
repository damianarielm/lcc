// gcc ejercicio2.c

#include <stdio.h> // printf

// Intercambia dos variables mediante XOR
void xswap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}

// Intercambia tres variables mediante XOR
void xswap3(int* a, int* b, int* c) {
	xswap(a,b);
	xswap(a,c);
}

void main () {
	int a = 1, b = 2, c = 3;

	printf("Antes: A=%d, B=%d, C=%d\n", a, b ,c);	
	xswap3(&a, &b, &c);
	printf("Despues: A=%d, B=%d, C=%d\n", a, b ,c);	
}
