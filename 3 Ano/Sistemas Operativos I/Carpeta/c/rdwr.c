// gcc rdwr.c -pthread

#include <stdio.h> // printf
#include <stdlib.h> // malloc, random
#include <unistd.h> // sleep
#include <assert.h> // assert
#include <pthread.h> // pthread_...
#include "colors.h" // colors

#define LECTORES 15
#define ESCRITORES 7
#define DELAY1 (sleep(random()%5))
#define DELAY2 (sleep(random()%45+5))

#define readlock(s) (rwlock(Lector, s))
#define writelock(s) (rwlock(Escritor, s))
#define readunlock(s) (rwunlock(Lector, s))
#define writeunlock(s) (rwunlock(Escritor, s))

enum TIPO { Lector, Escritor };

// Estructura para sincronizaciones
typedef struct {
	int leyendo, escribiendo;
	pthread_mutex_t* sem;
	pthread_cond_t *wrfinish, *rdfinish;
} *RWmutex_t;

RWmutex_t sincronizaciones;
int compartida;

RWmutex_t rwlock_init() {
	// Reserva memoria para la estructura
	RWmutex_t ret;
	ret = malloc(sizeof(*ret));

	/* Inicializaciones */

	// Nadie leyendo ni escribiendo
	ret->leyendo = ret->escribiendo = 0;

	// Inicializa el mutex
	ret->sem = malloc(sizeof(*ret->sem));
	pthread_mutex_init(ret->sem, 0);

	// Inicializa variables de condicion
	ret->wrfinish = malloc(sizeof(*ret->wrfinish));
	ret->rdfinish = malloc(sizeof(*ret->rdfinish));
	pthread_cond_init(ret->wrfinish, 0);
	pthread_cond_init(ret->rdfinish, 0);

	return ret;
}

void rwlock(enum TIPO tipo, RWmutex_t n) {
	pthread_mutex_lock(n->sem);
		switch(tipo) {
			case Lector:
				// Si hay gente escribiendo suelta el mutex y espera a que termine
				while(n->escribiendo) pthread_cond_wait(n->wrfinish, n->sem);
				n->leyendo++;
				break;
			case Escritor:
				// Si hay gente leyendo o escribiendo suelta el mutex y espera a que terminen
				while(n->leyendo || n->escribiendo) pthread_cond_wait(n->rdfinish, n->sem);
				n->escribiendo++;
				break;
		}
	pthread_mutex_unlock(n->sem);
}

void rwunlock(enum TIPO tipo, RWmutex_t n) {
	switch(tipo) {
		case Lector:
			pthread_mutex_lock(n->sem);
				n->leyendo--;
				pthread_cond_signal(n->rdfinish); // Avisa al escritor que termino la lectura
			pthread_mutex_unlock(n->sem);
			break;
		case Escritor:
			pthread_mutex_lock(n->sem);
				n->escribiendo--;
				pthread_cond_broadcast(n->wrfinish); // Avisa a todos los lectores que termino la escritura
			pthread_mutex_unlock(n->sem);
			break;
	}
}

void* reader (void* arg) {
	int quien = * (int*) arg;

	while (1) {
		readlock(sincronizaciones);
			printf(GREEN "Lector %d leyendo (lectores: %d, escritores %d)\n", quien, sincronizaciones->leyendo, sincronizaciones->escribiendo);
			compartida = quien;
			DELAY1;
			printf(RED "Lector %d saliendo (lectores: %d, escritores %d)\n", quien, sincronizaciones->leyendo, sincronizaciones->escribiendo);
		readunlock(sincronizaciones);
		DELAY2;
	}

	return NULL;
}

void* writer (void* arg) {
	int quien = * (int*) arg;

	while (1) {
		writelock(sincronizaciones);
			printf(YELLOW "Escritor %d escribiendo ", quien);
			printf("(lectores: %d, ", sincronizaciones->leyendo);
			printf("escritores: %d)\n", sincronizaciones->escribiendo);
			compartida = quien;
			DELAY1;
			assert(compartida == quien);
			printf(BLUE "Escritor %d saliendo ", quien);
			printf("(lectores: %d, ", sincronizaciones->leyendo);
			printf("escritores: %d)\n", sincronizaciones->escribiendo);
		writeunlock(sincronizaciones);
		DELAY1;
	}

	return NULL;
}

void main() {
	pthread_t r[LECTORES], w[ESCRITORES];
	int arg_r[LECTORES], arg_w[ESCRITORES], i, pid = 0;
	sincronizaciones = rwlock_init();

	// Crea los lectores
	for(i = 0; i < LECTORES; i++) {
		arg_r[i] = pid++;
		pthread_create(&r[i], 0, reader, &arg_r[i]);
	}

	// Crea los escritores
	for(i = 0; i < ESCRITORES; i++) {
		arg_w[i] = pid++;
		pthread_create(&w[i], 0, writer, &arg_w[i]);
	}

	pthread_join(r[0], NULL);
}
