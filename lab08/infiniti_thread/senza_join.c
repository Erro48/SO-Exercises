#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MSG_LENGTH 50

void* threadBody(void* arg) {
	int index = *((int*)arg);
	free(arg);
	
	printf("[Thread] indice passato: %i\n", index);
	pthread_exit((void*)(&index));
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
	int i = 0, createErr;
	int *p;
	pthread_t *tid;
	for (i=0;;i++) {
		tid = (pthread_t*)malloc(sizeof(pthread_t));
		p = (int*)malloc(sizeof(int));
		*p = i;
		createErr = pthread_create(tid, NULL, threadBody, (void*)p);
		printStrErr(createErr, "pthread_create");
	}



	return(0);
}
