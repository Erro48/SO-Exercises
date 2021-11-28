#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define STRLEN 100
#define NTHREAD 4
#define DELAY 1

typedef struct struttura {
	int N;
	char Str[STRLEN];
	int Indice;
} struttura;

void * threadBody(void* arg) {
	sleep(DELAY);
	struttura *arr = (struttura*)arg;
	printf("[DEBUG] N: %i, Indice: %i\n", arr->N, arr->Indice);
	char msg[STRLEN], nstr[2], indicestr[2];
	snprintf(nstr, 2, "%d", arr->N);
	snprintf(indicestr, 2, "%d", arr->Indice);
	strcpy(msg, nstr);
	strcat(msg, " ");
	strcat(msg, indicestr);
	strcpy(arr->Str, msg);
	if (arr->N > 1) {
		int i;
		int *val;
		pthread_t* tid;
		struttura *args;
		tid = (pthread_t*)malloc(sizeof(pthread_t) * arr->N);
		args = (struttura*)malloc(sizeof(struttura) * arr->N);
		for (i=0; i<arr->N; i++) {
			val = (int*)malloc(sizeof(int));
			(args + i)->N = arr->N - 1;
			(args + i)->Indice = i;
			pthread_create((tid + i), NULL, threadBody, (void*)args);
		}
	} else {
		printf("Fine thread [%s]\n", arr->Str);
	}
	pthread_exit(NULL);
	return NULL;
}

int main() {
	int i;
	int errCreate;
	struttura arr[NTHREAD];
	pthread_t tid[NTHREAD];
	for (i = 0; i < NTHREAD; i++) {
		arr[i].N = NTHREAD - 1;
		arr[i].Indice = i;
		printf("Creato il thread %i\n", i);
		errCreate = pthread_create(&tid[i], NULL, threadBody, (void*)&arr[i]);
		if(errCreate != 0) printf("Errore: %i\n", errCreate);
	}
	pthread_exit(0);
	return 0;
}
