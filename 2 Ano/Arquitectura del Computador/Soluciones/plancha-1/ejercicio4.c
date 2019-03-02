// gcc ejercicio4.c

#include <stdio.h> // printf

unsigned mult(unsigned a, unsigned b) {
	if (!b) return 0; // b == 0
	if (b == 1) return a; // b == 1
	if (!(b & 1)) return mult((a<<1), (b>>1)); // b par
	else return mult((a<<1), (b>>1)) + a; // b impar
}

void main() {
	int a, b;

	printf("Ingrese un numero: "); scanf("%d", &a);
	printf("Ingrese otro numero: "); scanf("%d", &b);
	printf("El producto es: %d\n", mult(a, b));
}
