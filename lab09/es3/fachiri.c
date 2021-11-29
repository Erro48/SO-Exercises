#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define SWORDS_NUM 10

void* fakir(void* args);

pthread_mutex_t swords[SWORDS_NUM];

int main() {
	int errCre;
	pthread_t tid1, tid2;
	errCre = pthread_create(&tid1, NULL, fakir, NULL);
	if (errCre != 0) printf("[ERROR:1] code: %i\n", errCre);

	errCre = pthread_create(&tid2, NULL, fakir, NULL);
	if (errCre != 0) printf("[ERROR:2] code: %i\n", errCre);

	pthread_exit(0);
	return 0;
}

void * fakir(void* args) {

	pthread_exit(NULL);
}
