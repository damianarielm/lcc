#include <stdio.h> // printf
#include <signal.h> // SIGINT, SIG_DFL, signal

void handler(int sig) {
	static int cuantas = 0;
	if (cuantas++ < 3) printf("Osoo!\n");
	else { printf("Volviendo a la normalidad.\n"); signal(SIGINT, SIG_DFL); }
}

void main() {
	signal(SIGINT, handler);
	printf("Bucle infinito...\n");
	while(1);
}
