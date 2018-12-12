// gcc intrazable.c -pthread

#include <stdio.h> // printf
#include <pthread.h> // pthread_...

#define CANTIDAD 25

void* f(void* arg) {
	static int quien;
	quien = * (int*) arg;
	printf("Hola mundo: %d\n", quien);
	return NULL;
}

void main() {
	pthread_t t[CANTIDAD];
	int arg[CANTIDAD], i;

	for(i = 0; i < CANTIDAD; i++) {
		arg[i] = i;
		pthread_create(&t[i], 0, f, &arg[i]);
	}

	for(i = 0; i < CANTIDAD; i++) pthread_join(t[i], NULL);
}
