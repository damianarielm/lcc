#include <stdio.h> // printf
#include <unistd.h> // fork

void main() {
	printf("Hola\n");
	if (fork() != 0) printf("Padre\n");
	else printf("Hijo\n");
	printf("Chau\n");
}
