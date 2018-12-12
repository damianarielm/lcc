// gcc pthreads.c -pthread

#include <stdio.h> // printf, NULL
#include <unistd.h> // sleep
#include <pthread.h> // pthread_t, pthread_create, pthread_join

int n;

void* f(void* arg) {
	int quien = * (int*) arg;

	while(1) {
		n = quien; // Region critica
		sleep(1);
		printf("Proceso %d: %s\n", quien, n == quien ? "Bien" : "Mal");
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
