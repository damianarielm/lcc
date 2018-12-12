// gcc pthreads.c -pthread

#include <stdio.h> // printf, NULL
#include <unistd.h> // sleep
#include <pthread.h> // pthread_...
#include <stdlib.h> // random

int n;
pthread_mutex_t critica = PTHREAD_MUTEX_INITIALIZER;

void* f(void* arg) {
	int quien = * (int*) arg;

	while(1) {
		pthread_mutex_lock(&critica); // Bloquea la region critica
		n = quien;
		sleep(random()%3);
		printf("Proceso %d: %s\n", quien, n == quien ? "Bien" : "Mal");
		pthread_mutex_unlock(&critica); // Libera la region critica
		sleep(random()%3);
	}

	return NULL;
}

void main() {
	pthread_t t1, t2;
	int arg1 = 1, arg2 = 2;

	pthread_create(&t1, 0, f, &arg1);
	pthread_create(&t2, 0, f, &arg2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}
