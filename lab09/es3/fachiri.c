#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define SWORDS_NUM 10

void* fakir(void* args);
void initSwords();

pthread_mutex_t mutex_swords[SWORDS_NUM];

int swords[SWORDS_NUM];

int main() {
	int errCre;
	int* val = (int*)malloc(sizeof(int));
	pthread_t tid1, tid2;
	initSwords();
	*val = 1;
	errCre = pthread_create(&tid1, NULL, fakir, (void*)val);
	if (errCre != 0) printf("[ERROR:1] code: %i\n", errCre);

	*val = 2;
	errCre = pthread_create(&tid2, NULL, fakir, (void*)val);
	if (errCre != 0) printf("[ERROR:2] code: %i\n", errCre);

	pthread_exit(0);
	return 0;
}

void initSwords() {
	int i;
	for (i = 0; i < SWORDS_NUM; i++) {
		swords[i] = 1;
	}
}

void * fakir(void* args) {
	while (1) {
		pthread_mutex_lock(
	}
	pthread_exit(NULL);
}
