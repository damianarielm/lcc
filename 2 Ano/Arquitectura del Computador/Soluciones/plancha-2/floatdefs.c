#include <stdio.h>
#include <math.h>
#include <ieee754.h>
#include "floatdefs.h"

/*
La norma ilcc2017 utiliza:
	1 bit para el signo,
	16 para la mantisa y
	18 para el exponente
con un sesgo de 30000
y 1 implicito
*/

void ilcc_print(ilcc n) {
	printf("%c%f * 2^%d", (n.negative ? '-' : '\0'), ilcc_significante(n), n.exponent-30000);
}

float ilcc_significante(ilcc n) {
	float m = 1.0;

	for (int i = 17; i >= 0; i--) {
		m = m + (n.mantissa & (1 << i) ? 1 : 0) * pow(2, i-18);
	}

	return m;
}
