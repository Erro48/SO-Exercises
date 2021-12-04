#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define SWORDS_NUM 10

void* fakir(void* args);
void initSwords();
void trafiggiti(int id, int* swords, int length);

pthread_mutex_t mutex_swords[SWORDS_NUM];

int swords[SWORDS_NUM];
int swords_index;

int main() {
	int errCre;
	int* val = (int*)malloc(sizeof(int));
	pthread_t tid1, tid2;

	initSwords();
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

void initSwords() {
	int i;
	for (i = 0; i < SWORDS_NUM; i++) {
		swords[i] = 1;
	}
}

void * fakir(void* args) {
	int id = *((int*)args);
	free(args);
	int *local_swords = (int*)malloc(sizeof(int) * SWORDS_NUM);
	int local_index = 0;
	while (1) {
		pthread_mutex_lock(&mutex_swords[swords_index]);
		
		if (swords_index == SWORDS_NUM - 1 && swords[swords_index] == 0) {
			/* ho finito le spade */
			trafiggiti(id, local_swords, local_index);
		}
		/* salvo in un array locale le spade che ho preso */
		*(local_swords + local_index) = swords_index;
		/* incremento l'indice locale dell'array locale */
		local_index++;
		/* imposto la spada `sword_index` come presa (0) */
		swords[swords_index] = 0;
		/* incremento l'indice globale */
		swords_index++;
		if (swords_index == SWORDS_NUM) swords_index--;

		pthread_mutex_unlock(&mutex_swords[swords_index]);
	}
	pthread_exit(NULL);
}

void trafiggiti (int id, int*  swords, int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("Fachiro %i: \"Mi sono trafitto con la spada %i!\"\n", id, *(swords + i));
	}
}
