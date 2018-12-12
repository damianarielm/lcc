// gcc softmutex.c -pthreads

#include <stdio.h> // printf, NULL
#include <stdlib.h> // random
#include <assert.h> // assert
#include <unistd.h> // sleep
#include <pthread.h> // pthread_...

#define PROCESOS 10
#define DELAY (random()%5)

volatile int choosing[PROCESOS], number[PROCESOS];
static int compartida;

int max() {
	int maximo = number[0], i;
	for(i = 1; i < PROCESOS; i++) if(number[i] > maximo) maximo = number[i];
	return maximo;
}

void lock(int pid) {
	int i;

	choosing[pid] = 1; // Eligiendo un numero...
	number[pid] = max() + 1; // Numero elegido
	choosing[pid] = 0; // ...listo
	// Sin embargo, dos procesos podrian haber sacado el mismo numero

	for(i = 0; i < PROCESOS; i++) {
		while(choosing[i]); // Espera mientras haya procesos sacando numero
		while(number[i] && // Espera mientras haya procesos con intenciones de entrar, siempre y cuando...
			(number[i] < number[pid] || // ...o bien quien tiene la intencion tiene un numero anterior...
			(number[i] == number[pid] && i < pid))); // ...o si tiene el mismo numero desempata por pid
	}
}

void unlock(int proc) { number[proc] = 0; }

void *f(void *arg) {
	int quien = * (int*) arg;

	while(1) {
		sleep(DELAY);

		lock(quien);
			compartida = quien;
			sleep(DELAY);
			printf("Proceso %d: %s\n", quien, compartida == quien?"Region critica protegida correctamente.":"Region critica vulnerada.");
			assert(compartida == quien);
		unlock(quien);
	}

	return NULL;
}

void main() {
	int arg[PROCESOS], i;
	pthread_t t[PROCESOS];

	// Crea todos los procesos
	for(i = 0; i < PROCESOS; i++){
		arg[i] = i;
		pthread_create(&t[i], 0, f, &arg[i]);
	}

	pthread_join(t[0], NULL);
}
