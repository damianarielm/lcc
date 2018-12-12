#include <stdio.h> // fprintf, printf
#include <string.h> // strcpy, strtok, strcat
#include <stdlib.h> // exit, getenv
#include <unistd.h> // access, X_OK

int main(int argc, char** argv) {
	char linea[1024], tmp[1024];
	char* p;

	if (argc != 2) {
		fprintf(stderr, "Argumentos insuficientes.\n");
		exit(-1);
	}
	
	strcpy(linea, getenv("PATH"));

	for (p = strtok(linea, ":"); p != NULL; p = strtok(NULL, ":")) {
		strcat(strcat(strcpy(tmp, p), "/"), argv[1]);
		if (access(tmp, X_OK) == 0) {
			printf("Ruta: %s\n", tmp);
			return 0;
		}
	}

	printf("%s no existe\n", argv[1]);
	return -1;
}

