#include "printerror.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "DBGpthread.h"

#define NTHREAD 5
#define DELAY 1

int arrivi[NTHREAD];
int ordine;

pthread_mutex_t mutex;
pthread_cond_t cond, condFine;

void initArrivi() {
	int i;
	for (i = 0; i < NTHREAD; i++) {
		arrivi[i] = 0;
	}
}

/* restituisce 1 l'unica cella a 0 in arrivi è arrivi[indice] */
int sonoUltimo(int indice) {
	int i;
	if (arrivi[indice]) return 0;
	for (i = 0; i < NTHREAD; i++) {
		if (i != indice && arrivi[i] == 0) {
			/* non sono l'ultimo */
			return 0;
		}
	}
	return 1;
}

int tuttiArrivati() {
	int i;
	for ( i = 0; i < NTHREAD; i++) {
		if (arrivi[i] == 0) return 0;
	}
	return 1;
}

void randomSleep() {
	int n = rand()%3;
	sleep(n);
}

void* threadBody(void* arg) {
	int indice, turno;
	int exit = 0;
	indice = *((int*)arg);
	free(arg);

	randomSleep();
	
	pthread_mutex_lock(&mutex);
	printf("Sono iniziato %i\n", indice);
	/* mi segno l'ordine di arrivo */
	turno = ordine;
	ordine++;
	/* sono passati tutti i thread */
	if (ordine >= NTHREAD) {
		ordine = 0;
	}
	pthread_mutex_unlock(&mutex);

	sleep(DELAY);

	pthread_mutex_lock(&mutex);

	if (sonoUltimo(indice)) {
		pthread_cond_broadcast(&cond);
	}
	arrivi[indice] = 1;

	if (!tuttiArrivati()) {
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock(&mutex);

	while (!exit) {
		pthread_mutex_lock(&mutex);
		if (ordine == turno) {
			exit = 1;
			ordine++;
		}
		pthread_mutex_unlock(&mutex);
	}
	
	printf("Sono finito %i\n", indice);

	pthread_exit(NULL);
}

int main() {
	int i;
	pthread_t tid[NTHREAD];
	srand(time(NULL));
	DBGpthread_mutex_init(&mutex, NULL, NULL);
	DBGpthread_cond_init(&cond, NULL, NULL);
	initArrivi();
	ordine = 0;
	for (i = 0; i < NTHREAD; i++) {
		int* t;
		t = (int*)malloc(sizeof(int));
		*t = i;
		pthread_create(&tid[i], NULL, threadBody, (void*)t);
	}
	pthread_exit(NULL);
	return 0;
}
