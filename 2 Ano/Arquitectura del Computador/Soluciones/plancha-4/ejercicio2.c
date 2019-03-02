// arm-linux-gnueabi-gcc ejercicio2.c ejercicio2.s -static
// qemu-arm ./a.out

#include <stdio.h>

unsigned int campesino_ruso(unsigned int, unsigned int);

void main() {
	int a,b;

	printf("Ingrese un numero: ");
	scanf("%d", &a);
	printf("Ingrese un numero: ");
	scanf("%d", &b);

	printf("%d * %d = %d\n", a, b, campesino_ruso(a,b));
}
