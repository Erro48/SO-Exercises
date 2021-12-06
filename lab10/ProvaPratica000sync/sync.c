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

pthread_mutex_t mutex;
pthread_cond_t cond;

void initArrivi() {
	int i;
	for (i = 0; i < NTHREAD; i++) {
		arrivi[i] = 0;
	}
}

/* restituisce 1 l'unica cella a 0 in arrivi è arrivi[indice] */
int sonoUltimo(int indice) {
	if (arrivi[indice]) return 0;
	int i;
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

void* threadBody(void* arg) {
	int indice;
	indice = *((int*)arg);
	free(arg);
	printf("Sono iniziato %i\n", indice);

	sleep(DELAY);

	pthread_mutex_lock(&mutex);

	if (sonoUltimo(indice)) {
		pthread_cond_broadcast(&cond);
	}
	arrivi[indice] = 1;

	if (!tuttiArrivati()) {
		pthread_cond_wait(&cond, &mutex);
	}
	printf("Sono finito %i\n", indice);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main() {
	DBGpthread_mutex_init(&mutex, NULL, NULL);
	DBGpthread_cond_init(&cond, NULL, NULL);
	int i;
	pthread_t tid[NTHREAD];
	initArrivi();
	for (i = 0; i < NTHREAD; i++) {
		int* t;
		t = (int*)malloc(sizeof(int));
		*t = i;
		pthread_create(&tid[i], NULL, threadBody, (void*)t);
	}
	pthread_exit(NULL);
	return 0;
}
