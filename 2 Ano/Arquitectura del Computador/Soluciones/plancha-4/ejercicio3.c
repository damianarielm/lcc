// arm-linux-gnueabi-gcc ejercicio3.c ejercicio3.s -static
// qemu-arm ./a.out

#include <stdio.h>

int shiftleft(int);

void main() {
	int a;

	printf("Ingrese el exponente: ");
	scanf("%d", &a);

	printf("2^%d = %d\n", a, shiftleft(a));
}
