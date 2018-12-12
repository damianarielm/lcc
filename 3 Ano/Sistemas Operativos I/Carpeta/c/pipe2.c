#include <stdio.h> // putchar
#include <unistd.h> // fork, pipe, write, read, close
#include <wait.h> // wait

void main() {
	int pip[2];
	pipe(pip);

	if (fork()) { // El padre escribe en el pipe
		write(pip[1], "Hola mundo\n", 11);
		close(pip[0]);
		close(pip[1]);
		wait(NULL);
	} else { // El hijo lee del pipe
		char c;
		close(pip[1]); // Posicion correcta
		while (read(pip[0], &c, 1) == 1) putchar(c);
		close(pip[0]);
		close(pip[1]); // Posicion incorrecta
	}
}
