// gcc prodcons.c -pthread

#include <stdio.h> // printf
#include <pthread.h> // pthread_...
#include <stdlib.h> // random
#include <unistd.h> // sleep

#include "colors.h" // colores

#define CASILLEROS 15
#define DELAYPROD 4 // Segundos
#define DELAYCONS 7 // Segundos

int buffer[CASILLEROS];
int in = 0, out = 0, producidas = 0;

pthread_mutex_t s = PTHREAD_MUTEX_INITIALIZER;

// Colas de bloqueo
pthread_cond_t lleno = PTHREAD_COND_INITIALIZER;
pthread_cond_t vacio = PTHREAD_COND_INITIALIZER;

void printbuf(int pos, char* color) {
	int i;

	printf("[ ");
	for (i = 0; i < CASILLEROS; i++) {
		if (i == pos) printf("%s", color);
		printf("%d ", buffer[i]);
		printf(WHITE);
	}
	printf("]\n\n");
}

void* productor(void* arg) {
	while(1) {
		sleep(random()%DELAYPROD);
		pthread_mutex_lock(&s);
		while(producidas >= CASILLEROS) pthread_cond_wait(&lleno, &s);
		buffer[in] = 1;
		printf("Produccion realizada:\t"); printbuf(in, GREEN);
		in = (in + 1)%CASILLEROS;
		producidas++;
		pthread_cond_signal(&vacio); //pthread_cond_broadcast(&vacio);
		pthread_mutex_unlock(&s);
	}
	return NULL;
}

void* consumidor(void* arg) {
	while(1) {
		sleep(random()%DELAYCONS);
		pthread_mutex_lock(&s);
		while(producidas <= 0) pthread_cond_wait(&vacio, &s);
		buffer[out] = 0;
		printf("Producto consumido:\t"); printbuf(out, RED);
		out = (out + 1)%CASILLEROS;
		producidas--;
		pthread_cond_signal(&lleno);
		pthread_mutex_unlock(&s);
	}
	return NULL;
}

void main() {
	pthread_t p,c;

	pthread_create(&p, 0, productor, NULL);
	pthread_create(&c, 0, consumidor, NULL);

	pthread_join(p, NULL);
	pthread_join(c, NULL);
}

