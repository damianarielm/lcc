// gcc ejercicio3.c ejercicio3.s

#include <stdio.h>
#include <malloc.h>

#define MAX_STRING 50

int fuerzabruta(char* S, char* s, unsigned lS, unsigned ls);

int len(char* string) {
	int i = 0;
	while (string[i] != '\0') i++;
	return i;
}

void main() {
	char S[MAX_STRING];
	char s[MAX_STRING];

	printf("Ingrese la cadena donde buscar: ");
	gets(S);

	printf("Ingrese la cadena a buscar: ");
	gets(s);

	printf("La cadena se encuentra en la posicion: %d\n", fuerzabruta(S, s, len(S), len(s)));
}
