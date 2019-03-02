#include <stdio.h>

int f(char a, int b, char c, long d, char e, short f, int g, int h) {
	printf("a: %p\n", &a);
	printf("b: %p\n", &b);
	printf("c: %p\n", &c);
	printf("d: %p\n", &d);
	printf("e: %p\n", &e);
	printf("f: %p\n", &f);
	printf("g: %p\n", &g);
	printf("h: %p\n", &h);
	return 0;
}

int main() {
	return f('1', 2, '3', 4, '5', 6, 7, 8);
}
