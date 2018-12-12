#include <stdio.h> // printf
#include <wait.h> // wait, signal, SIGCHLD
#include <unistd.h> // fork, NULL, sleep
#include <stdlib.h> // random

int flag;

void handler (int sig) { wait(NULL); flag = 1; }

void main() {
	signal(SIGCHLD, handler);
	if (fork()) {
		while(flag == 0) { // Cuidado con optimizaciones
			printf("Padre trabajando hasta que muera el hijo...\n");
			sleep(random()%3);
		}
	} else {
		for (int i = 0; i < 5; i++) {
			printf("Hijo trabajando...\n");
			sleep(random()%3);
		}
	}
}
