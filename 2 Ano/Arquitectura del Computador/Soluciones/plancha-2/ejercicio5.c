// gcc ejercicio5.c

/*
Observemos primero que ambos numeros tienen el mismo exponente.

(00110000)_2 = (2^4 + 2^5)_10 = 16 + 32 = 48
Es decir: 48 - 127 = -79

OPCION 1: PASANDO DE IEEE754 A DECIMAL
======================================

Calculo del significante:
-------------------------
(1.101)_2 = (2 + 2^-1 + 2^-3)_10 = (1.625)_10

Calculo del numero:
-------------------
1.75 * 2^(-79) + 1.625 * 2^(-79) = (1.75 + 1.625) * 2^(-79) =
= 3.375 * 2^(-79)

OPCION 2: PASANDO DE DECIMAL A IEEE754
======================================

Parte entera:
-------------
(1)_10 = (1)_2

Calculo de la mantisa:
----------------------
0.75 * 2 = 1.5
0.5 * 2 = 1
0 * 2 = 0

Es decir: (0.75)_10 = (0.11)_2

Finalmente (1.75 * 2^-79)_10 = (0 00110000 11000000000000000000000)_IEEE754

Suma de los significantes:
--------------------------
 1.11000000000000000000000
 1.10100000000000000000000

10.10110000000000000000000

Normalizando:
-------------
1.01011000000000000000000
Correcion del exponente: 49

Por lo tanto la suma sera: (0 00110001 01011000000000000000000)_IEEE754
*/

#include <stdio.h> // printf
#include <ieee754.h> // union ieee754_float
#include <math.h> // pow

void main() {
	float n1 = 1.75 * pow(2, -79);

	// 0 00110000 101 0000 0000 0000 0000 0000
	union ieee754_float n2;
	n2.ieee.negative = 0;
	n2.ieee.exponent = 48;
	n2.ieee.mantissa = 5 << 20;

	union ieee754_float n3;
	n3.ieee.negative = 0;
	n3.ieee.exponent = 49;
	n3.ieee.mantissa = 11 << 19;

	float resultado = n1 + n2.f;

	printf("Valor real: %e\n\n", resultado);

	printf("Calculo de IEEE754 a Decimal: %e\n", 3.375 * pow(2,-79));
	printf("Calculo de Decimal a IEEE754: %e\n", n3.f);
}
