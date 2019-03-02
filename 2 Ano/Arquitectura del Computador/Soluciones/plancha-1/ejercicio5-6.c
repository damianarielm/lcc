// gcc ejercicio5-6.c bitsdef.c -lgmp

#include <limits.h> // CHAR_BIT
#include <stdio.h> // printf
#include <malloc.h> // malloc

#include "bitsdef.h" // print

int es_par(nro n) { return (!(n.n[0] & 1)); }

nro* izq(nro* n, int c) {
	if (!c) return n; // c == 0

	nro* resultado = malloc(sizeof(nro));
	for (int i = 0; i < 16; i++) resultado->n[i] = n->n[i]; // Copia el numero

	resultado->n[15] = resultado->n[15] << 1;

	for (int i = 14; i >= 0; i--) {
		if (resultado->n[i] & (1 << sizeof(short)*CHAR_BIT-1)) resultado->n[i+1] = resultado->n[i+1] | 1;
		resultado->n[i] = resultado->n[i] << 1;
	}

	return izq(resultado, --c);
}

nro* der(nro* n, int c) {
	if (!c) return n; // c == 0

	nro* resultado = malloc(sizeof(nro));
	for (int i = 0; i < 16; i++) resultado->n[i] = n->n[i]; // Copia el numero

	resultado->n[0] = resultado->n[0] >> 1;

	for (int i = 1; i <= 15; i++) {
		if (resultado->n[i] & 1) resultado->n[i-1] = resultado->n[i-1] | (1 << sizeof(short)*CHAR_BIT-1);
		resultado->n[i] = resultado->n[i] >> 1;
	}

	return der(resultado, --c);
}

int es_cero(nro* n) {
	for (int i = 0; i < 16; i++) if (n->n[i]) return 0;
	return 1;
}

int es_uno(nro* n) {
	for (int i = 15; i > 0; i--) if (n->n[i]) return 0;
	return n->n[0] == 1;
}

nro* add(nro* a, nro* b) {
	nro* resultado = malloc(sizeof(nro));
	for (int i = 0; i < 16; i++) resultado->n[i] = a->n[i]; // Copia el numero a

	int t, overflow = 0;
	for (int i = 0; i < 15; i++) {
		resultado->n[i] += b->n[i] + overflow;
		t = a->n[i] + b->n[i];
		if (t > (1 << sizeof(short)*CHAR_BIT)-1) overflow = 1;
		else overflow = 0;
	}

	return resultado;
}

nro* mult(nro* a, nro* b) {
	nro retorno; // Variable de retorno
	for (int i = 0; i < 16; i++) retorno.n[i] = 0; // Inicializa en 0

	if (es_cero(b)) return b; // b == 0
	if (es_uno(b)) return a; // b == 1
	if (es_par(*b)) { // b par
		a = izq(a,1);
		b = der(b,1);
		return mult(a, b);
	}
	else return add(mult(izq(a,1), der(b,1)), a);  // b impar
}

void main() {
	nro a;
	for (int i = 0; i < 16; i++) a.n[i] = 0; // Inicializa en 0
	a.n[0] = 12; // Inicializa en 12

	nro b;
	for (int i = 0; i < 16; i++) b.n[i] = 0; // Inicializa en 0
	b.n[0] = 3; // Inicializa en 3

	nro c;
	for (int i = 0; i < 16; i++) c.n[i] = 0; // Inicializa en 0
	c.n[0] = -1; // Inicializa en 65535

	printf("Numero A: "); print(a);
	printf("Numero B: "); print(b);
	printf("Numero C: "); print(c);
	printf("A es 0?: %d\n", es_cero(&a));
	printf("A es 1?: %d\n", es_uno(&a));
	printf("A >> 1 = "); print(*der(&a,1));
	printf("A << 1 = "); print(*izq(&a,1));
	printf("C << 2 = "); print(*izq(&c, 2));
	printf("(C << 2) + C = "); print(*add(izq(&c, 2),&c));
	printf("A + B = "); print(*add(&a, &b));
	printf("A * B = "); print(*mult(&a, &b));
}
