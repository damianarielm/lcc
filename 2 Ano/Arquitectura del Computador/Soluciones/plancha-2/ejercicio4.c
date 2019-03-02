// gcc ejercicio4.c floatdefs.c -lm

// Menor numero: 1 * 2^(-30000)
// Mayor numero: 0.9999961853 * 2^101071

#include <stdio.h>
#include <math.h>
#include "floatdefs.h"

ilcc suma(ilcc n1, ilcc n2) {
	ilcc resultado;

	resultado.exponent = n2.exponent; // Inicializa el exponente

	// Inicializa el signo
	if (n1.negative && n2.negative) resultado.negative = 1;
	else if (!n1.negative && !n2.negative) resultado.negative = 0;
	else {
		if (n1.exponent == n2.exponent) resultado.negative = (n1.mantissa > n2.mantissa) ? n1.negative : n2.negative;
		else resultado.negative = (n1.exponent > n2.exponent) ? n1.negative : n2.negative;
	}

	// Dejamos un lugar para agregar el 1 implicito
	n1.mantissa >>= 1;
	n2.mantissa >>= 1;

	// Agregamos el 1 implicito
	n1.mantissa |= (1 << 17);
	n2.mantissa |= (1 << 17);

	// Igualando exponentes
	if (n1.exponent < n2.exponent) {
		// Corremos la mantisa, segun la correccion del exponente
		n1.mantissa >>= (n2.exponent - n1.exponent);
	}
	else if (n1.exponent != n2.exponent) {
		// Corremos la mantisa, segun la correccion del exponente
		n2.mantissa >>= (n1.exponent - n2.exponent);

		resultado.exponent = n1.exponent;
	}

	// Sumamos las mantisas desplazadas por si hay acarreo
	if (n1.negative == n2.negative) resultado.mantissa = (n1.mantissa >> 1) + (n2.mantissa >> 1);
	else resultado.mantissa = (n2.mantissa) - (n1.mantissa);

	// Normalizamos el resultado
	if ((resultado.mantissa & (1 << 17)) == 0) { // No hubo acarreo
		resultado.mantissa <<= 2;
	} else { // Si hubo acarreo
		resultado.mantissa <<= 1;
		resultado.exponent++;

	}

	return resultado;
}

ilcc producto(ilcc n1, ilcc n2) {
	ilcc resultado;

	resultado.exponent = n2.exponent + n1.exponent - 30000; // Inicializa el exponente

	// Inicializa el signo
	resultado.negative = n1.negative != n2.negative;

	// Dejamos un lugar para agregar el 1 implicito
	n1.mantissa >>= 1;
	n2.mantissa >>= 1;

	// Agregamos el 1 implicito
	n1.mantissa |= (1 << 17);
	n2.mantissa |= (1 << 17);

	//Multiplicamos las mantisas en un dato mas grande, y acomodamos
	resultado.mantissa = (unsigned long long) n1.mantissa * n2.mantissa >> 18;

	// Normalizamos el resultado
	for (int i = 17; (i > 0 && ((resultado.mantissa & (1 << 17)) == 0)); i--) {
		resultado.mantissa <<= 1;
	}
	resultado.mantissa <<= 1;

	return resultado;	
}

void main () {
	ilcc n1;
	n1.negative = 0;
	n1.exponent = 30003;
	n1.mantissa = 1 << 10;

	ilcc n2;
	n2.negative = 0;
	n2.exponent = 30005;
	n2.mantissa = 1 << 5;

	ilcc resultado1 = suma(n1, n2);
	ilcc resultado2 = producto(n1, n2);

	printf("Numero 1: "); ilcc_print(n1); printf(" = %lf\n", pow(-1, n1.negative) * ilcc_significante(n1) * pow(2, n1.exponent-30000));
	printf("Numero 2: ");	ilcc_print(n2); printf(" = %lf\n", pow(-1, n2.negative) * ilcc_significante(n2) * pow(2, n2.exponent-30000));
	puts("");
	printf("Numero 1 + Numero 2: "); ilcc_print(resultado1); printf(" = %lf\n", pow(-1, resultado1.negative) * ilcc_significante(resultado1) * pow(2, resultado1.exponent-30000));
	printf("Numero 1 * Numero 2: "); ilcc_print(resultado2); printf(" = %lf\n", pow(-1, resultado2.negative) * ilcc_significante(resultado2) * pow(2, resultado2.exponent-30000));
}
