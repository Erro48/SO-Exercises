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

void setStr(struttura* s);
void printStruct(struttura s);
void printStructShort(struttura s);
void createThreadCtrlError(pthread_t* tid, void* args);
void* threadBody(void* args);

void setStr(struttura* s) {
	char* sindice[2];
	snprintf(s->Str, STRLEN, "%d", s->N);
	snprintf(sindice, 2, "%d", s->Indice);
	strcat(s->Str, " ");
	strcat(s->Str, sindice);
}

void printStruct(struttura s) {
	printf("Struttura:\n");
	printf(" - N:\t\t%i\n", s.N);
	printf(" - Str:\t\t%s\n", s.Str);
	printf(" - Indice:\t%i\n\n", s.Indice);
}

void printStructShort(struttura s) {
	int i,j;
	for (i=0; i<NTHREAD - 1 - s.N; i++) {
		printf("\t");
	}
	for (j=0; j<s.Indice; j++) {
		printf(" ");
	}
	printf("{ %s }\n", s.Str);
}

void createThreadCtrlError(pthread_t* tid, void* args) {
	int err;
	err = pthread_create(tid, NULL, threadBody, args);
	if (err != 0) {
		printf("[ERROR] %d\n", err);
	}
}

void * threadBody(void* arg) {
	/* Aspetta 1 secondo */
	sleep(DELAY);
	/* Legge il contenuto della struttura ricevuta */
	struttura *arr = (struttura*)arg;
	setStr(arr);
	printStructShort(*arr);

	if (arr->N > 1) {
		int i;
		pthread_t* tid;
		struttura *args;
		tid = (pthread_t*)malloc(sizeof(pthread_t) * arr->N);
		for (i = 0; i < arr->N - 1; i++) {
			args = (struttura*)malloc(sizeof(struttura));
			args->N = arr->N - 1;
			args->Indice = i;
/*			printf("\n------------| %i |------------\n%i %i\n", i, (args + i)->N, (args + i)->Indice);*/
			pthread_create((tid + i), NULL, threadBody, (void*)args);
		}
		for (i = 0; i < arr->N - 1; i++) {
			pthread_join((tid + i), (void**)&args);
			printf("Dopo join ");
			printStructShort(*args);
		}
	}
	pthread_exit(arr);
	return NULL;
}

int main() {
	int i;
	int errCreate;
	struttura arr[NTHREAD];
	pthread_t tid[NTHREAD];
	struttura *str;
	for (i = 0; i < NTHREAD; i++) {
		arr[i].N = NTHREAD - 1;
		arr[i].Indice = i;
		printf("Creato il thread %i\n", i);
		errCreate = pthread_create(&tid[i], NULL, threadBody, (void*)&arr[i]);
		if(errCreate != 0) printf("Errore: %i\n", errCreate);
	}
	for (i = 0; i < NTHREAD; i++) {
		pthread_join(&tid[i], (void**)&str);
	}
	pthread_exit(0);
	return 0;
}
