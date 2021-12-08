#include "printerror.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "DBGpthread.h"

#define NTHREAD 5
#define DELAY 1

int arrives[NTHREAD];
int order;

pthread_mutex_t mutex;
pthread_cond_t cond, condExit;

void initArrives() {
	int i;
	for (i = 0; i < NTHREAD; i++) {
		arrives[i] = 0;
	}
}

/* returns 1 if the only cell set to 0 is arrives[index] */
int lastThread(int index) {
	int i;
	if (arrives[index]) return 0;
	for (i = 0; i < NTHREAD; i++) {
		if (i != index && arrives[i] == 0) {
			/* not last */
			return 0;
		}
	}
	return 1;
}

int allArrived() {
	int i;
	for ( i = 0; i < NTHREAD; i++) {
		if (arrives[i] == 0) return 0;
	}
	return 1;
}

void randomSleep() {
	int n = rand()%3;
	sleep(n);
}

void* threadBody(void* arg) {
	int index, turn;
	int exit = 0;
	index = *((int*)arg);
	free(arg);

	randomSleep();
	
	pthread_mutex_lock(&mutex);
	printf("Start %i\n", index);
	/* set the arrival order */
	turn = order;
	order++;
	/* all threads are gone */
	if (order >= NTHREAD) {
		order = 0;
	}
	pthread_mutex_unlock(&mutex);

	sleep(DELAY);

	pthread_mutex_lock(&mutex);

	if (lastThread(index)) {
		pthread_cond_broadcast(&cond);
	}
	arrives[index] = 1;

	if (!allArrived()) {
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock(&mutex);

	while (!exit) {
		pthread_mutex_lock(&mutex);
		if (order == turn) {
			exit = 1;
			order++;
		}
		pthread_mutex_unlock(&mutex);
	}
	
	printf("End %i\n", index);

	pthread_exit(NULL);
}

int main() {
	int i;
	pthread_t tid[NTHREAD];
	srand(time(NULL));
	DBGpthread_mutex_init(&mutex, NULL, NULL);
	DBGpthread_cond_init(&cond, NULL, NULL);
	initArrives();
	order = 0;
	for (i = 0; i < NTHREAD; i++) {
		int* t;
		t = (int*)malloc(sizeof(int));
		*t = i;
		pthread_create(&tid[i], NULL, threadBody, (void*)t);
	}
	pthread_exit(NULL);
	return 0;
}
