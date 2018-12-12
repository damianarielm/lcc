#include <stdio.h> // perror, putchar
#include <string.h> // strlen, NULL
#include <unistd.h> // pipe, fork, write, close, execl
#include <stdlib.h> // exit
#include <wait.h> // wait

void main() {
	char *arreglo[] = { "Es", "muy", "facil", "atrapar", "custodiando", "continuamente", "hispanoamericanas", "internacionalizadas", "anticonstitucionalmente", NULL};
	int pip[2];
	pipe(pip);

	if (fork()) {
		int i;
		char c;

		// El padre escribe las palabras en el pipe, que seran la entrada de sort
		for (i = 0; arreglo[i] != NULL; i++) {
			write(pip[1], arreglo[i], strlen(arreglo[i]));
			write(pip[1], "\n", 1);
		}
		close(pip[1]);

		// El padre escibre lo que lea del pipe, que sera la salida de sort
		while (read(pip[0], &c, 1) == 1) putchar(c);

		close(pip[0]);
		wait(NULL);
	} else {
		// La entrada standard ahora sera lo que escriba el padre en el pipe
		close(0); dup(pip[0]); close(pip[0]);

		// La salida standard ahora sera lo que lea el padre del pipe
		close(1); dup(pip[1]); close(pip[1]);

		execl("/usr/bin/sort", "sort", NULL);
		perror("execl");
		exit(-1);
	}
}
