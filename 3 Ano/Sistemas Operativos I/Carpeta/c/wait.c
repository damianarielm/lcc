#include <stdio.h> // printf
#include <unistd.h> // fork
#include <wait.h> // wait

void main() {
	if (fork() != 0) { // Padre
		int status;
		wait(&status);
		printf("Padre %d\n", status);
	} else {
		printf("Hijo\n");
	}
}
