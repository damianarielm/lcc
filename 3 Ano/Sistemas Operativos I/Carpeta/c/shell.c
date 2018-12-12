#include <stdio.h> // printf
#include <string.h> // strlen, strcmp
#include <unistd.h> // fork, execl
#include <stdlib.h> // exit
#include <wait.h> // wait

void main() {
	int status;
	char linea[1024];

	while(strcmp(linea, "fin")) {
		printf("Ingrese comando: ");
		fgets(linea, sizeof(linea), stdin);
		linea[strlen(linea) - 1] = 0;
		if (fork() == 0) exit(execl(linea, linea, NULL));
		wait(&status);
		if (WIFEXITED(status)) printf("Bien: %d\n", WEXITSTATUS(status));
		else printf("Mal: %d\n", WTERMSIG(status));
	}
}
