#include <stdio.h> // printf
#include <limits.h> // CHAR_BIT
#include <gmp.h> // print

#include "bitsdef.h"

void bits(int n) {
	for (int i = sizeof(n)*CHAR_BIT-1; i >= 0; i--) {
		printf("%d", n & (1 << i) ? 1 : 0); // Imprime el bit
		if (!(i % CHAR_BIT)) printf(" "); // Separa los bytes
	}

	puts("");
}

void print(nro n)
{
	int i;
	char str[1024];
	short sign[16], num[16];
	mpz_t n1, n2;
	for (i=0; i<15; i++) {
		num[i] = n.n[i];
		sign[i] = 0;
	}
	num[15] = n.n[15] & 0x7FFF;
	sign[15] = n.n[15] & 0x8000;
	mpz_init(n1);
	mpz_init(n2);
	mpz_import(n1, 16, -1, 2, 0, 0, num);
	mpz_import(n2, 16, -1, 2, 0, 0, sign);
	mpz_neg(n2, n2);
	mpz_add(n2, n1, n2);
	mpz_get_str(str, 10, n2);
	printf("Número: %s\n", str);
	mpz_clear(n1);
	mpz_clear(n2);
}