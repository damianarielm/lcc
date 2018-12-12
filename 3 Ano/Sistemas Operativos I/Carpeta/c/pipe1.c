#include <stdio.h> // printf
#include <unistd.h> // fork, pipe, write, read, close
#include <wait.h> // wait

void main() {
	int pip[2];
	pipe(pip);

	if (fork()) { // El padre escribe en el pipe
		write(pip[1], "Hola mundo", 10);
		close(pip[0]);
		close(pip[1]);
		wait(NULL);
	} else { // El hijo lee del pipe
		char linea[1024];
		int cuanto = read(pip[0], linea, sizeof(linea));
		linea[cuanto] = 0;
		printf("[%s]\n", linea);
		close(pip[0]);
		close(pip[1]);
	}
}
