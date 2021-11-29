#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define SWORDS_NUM 10

void* fakir(void* args);

pthread_mutex_t swords[SWORDS_NUM];

int swords_index;

int main() {
	int errCre;
	int* val = (int*)malloc(sizeof(int));
	pthread_t tid1, tid2;
	swords_index = 0;
	*val = 1;
	errCre = pthread_create(&tid1, NULL, fakir, (void*)val);
	if (errCre != 0) printf("[ERROR:1] code: %i\n", errCre);

	*val = 2;
	errCre = pthread_create(&tid2, NULL, fakir, (void*)val);
	if (errCre != 0) printf("[ERROR:2] code: %i\n", errCre);

	pthread_exit(0);
	return 0;
}

void * fakir(void* args) {
	
	pthread_exit(NULL);
}
