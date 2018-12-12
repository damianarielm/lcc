#include <stdio.h> // perror, putchar
#include <string.h> // strlen, NULL
#include <unistd.h> // pipe, fork, write, close, execl
#include <stdlib.h> // exit
#include <wait.h> // wait

void main() {
	char *arreglo[] = { "Es", "muy", "facil", "atrapar", "custodiando", "continuamente", "hispanoamericanas", "internacionalizadas", "anticonstitucionalmente", NULL};
	int ph[2], hp[2];
	pipe(ph); pipe(hp);

	if (fork()) {
		int i;
		char c;
		close(ph[0]); close(hp[1]);

		for (i = 0; arreglo[i] != NULL; i++) {
			write(ph[1], arreglo[i], strlen(arreglo[i]));
			write(ph[1], "\n", 1);
		}
		close(ph[1]);

		while(read(hp[0], &c, 1) == 1) putchar(c);

		close(hp[0]);
		wait(NULL);
	} else {
		close(ph[1]); close(hp[0]);
		close(0); dup(ph[0]); close(ph[0]);
		close(1); dup(hp[1]); close(hp[1]);

		execl("/usr/bin/sort", "sort", NULL);
		perror("execl");
		exit(-1);
	}
}
