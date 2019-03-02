// gcc ejercicio3.c

#include <stdio.h> // getchar
#include <stdlib.h> // atoi

int main(int argc, char** argv) {
	if (argc < 2) return 1;

	int c;

	do {
		c = getchar();
		putchar(c ^ atoi(argv[1]));
	} while (c != EOF);

	puts("");
}
