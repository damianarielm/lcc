// gcc ejercicio5.c ejercicio5.s

#include <stdio.h>
#include <setjmp.h>

int setjmp2(jmp_buf buffer);
int longjmp2(jmp_buf buffer, int ret);

static jmp_buf buffer;

void segunda() {
	printf("Segunda\n"); // Se imprime
	longjmp2(buffer, 1);
	/*
	Segunda deberia retornar a primera, sin embargo
	longjmp2 deuelve el programa al momento en donde
	se habia llamado a setjmp, pero modificando su
	valor de retorno.
	*/
}

void primera() {
	segunda(); // Se llama a segunda
	printf("Primera\n"); // No llega a imprimirse pues segunda no retorna
}

void main() {
	if (!setjmp2(buffer)) primera(); // setjmp2 devuelve 0 y se llama a primera
	else printf("Main\n"); // Tambien se imprime, pues longjmp2 modifico el retorno de setjmp2
}
