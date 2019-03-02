// arm-linux-gnueabihf-gcc ejercicio4.c ejercicio4.s -mfpu=vfp -march=armv7 -mfloat-abi=hard -static
// qemu-arm ./a.out

#include <stdio.h>

float determinante(float, float, float, float);

void main() {
	float a,b,c,d;

	printf("a b\nc d\n\n");

	printf("Ingrese el flotante a: ");
	scanf("%f", &a);
	printf("Ingrese el flotante b: ");
	scanf("%f", &b);
	printf("Ingrese el flotante c: ");
	scanf("%f", &c);
	printf("Ingrese el flotante d: ");
	scanf("%f", &d);

	printf("\nEl determinante es %f\n", determinante(a,b,c,d));
}
