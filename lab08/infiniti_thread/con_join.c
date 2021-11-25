#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MSG_LENGTH 50
#define N_THREADS 1000

void* threadBody(void* arg) {
	int index = *((int*)arg);
	free(arg);
	
	printf("[Thread] indice passato: %i\n", index);
	pthread_exit((void*)(&index));
	pthread_exit(NULL);
}

void printStrErr(int funcErr, char* funcName) {
	if (funcErr != 0) {
		char msg[MSG_LENGTH];
		int strErr;
		strErr = strerror_r(funcErr, msg, MSG_LENGTH);
		if (strErr != 0) { printf("[strerror_r] %i\n", strErr); }
		printf("[%s():ERROR] code: %i, msg: %s\n", funcName, funcErr, msg);
		fflush(stdout);
	}
}

int main() {
	int i, j, createErr, joinErr;
	int *p;
	pthread_t tid[N_THREADS];
	for (i=0;;i++) {
		for (j=0; j<N_THREADS; j++) {
			p = (int*)malloc(sizeof(int));
			*p = i;
			createErr = pthread_create(&tid[i], NULL, threadBody, (void*)p);
			printStrErr(createErr, "pthread_create");
		}
		
		for (j=0; j<N_THREADS; j++) {
			joinErr = pthread_join(tid[j], (void**)&p);
			printStrErr(joinErr, "pthread:join");
		}
	}


	pthread_exit(NULL);
	return(0);
}
