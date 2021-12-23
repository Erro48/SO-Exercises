#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

#include "printerror.h"

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#include "DBGpthread.h"

#define MAXNUMTHREAD 5
#define DELAYNEWRABBIT 5

pthread_mutex_t mutex;

int nThreadsAlive = 0;

void *rabbit(void* arg) {
	int rc, i=1;
	int argVal = *((int*)arg);
	int label = argVal;
	sleep(1);
	DBGpthread_mutex_lock(&mutex, "[print label] mutex_lock fail\n");
	printf("[%i] Thread %i\n", nThreadsAlive, label);
	DBGpthread_mutex_unlock(&mutex, "[print label] mutex_unlock fail\n");

	while (1) {
		DBGpthread_mutex_lock(&mutex, "[thread if] mutex_lock fail\n");
		if (nThreadsAlive < MAXNUMTHREAD) {
			pthread_t *tid = (pthread_t*)malloc(sizeof(pthread_t));
			int* val = (int*)malloc(sizeof(int));
			*val = argVal + i;
			rc = pthread_create(tid, NULL, rabbit, (void*)val);
			if (rc != 0) printf("[thread] pthread_create fail\n");
			else {
				printf("Thread %i created thread %i\n", label, *val);
				nThreadsAlive++;
			}
		} else {
			nThreadsAlive--;
			DBGpthread_mutex_unlock(&mutex, "[thread else] mutex_unlock fail\n");
			pthread_exit(NULL);
		}
		DBGpthread_mutex_unlock(&mutex, "[thread if] mutex_unlock fail\n");
		i++;
	}
}

int main ( int argc, char* argv[] ) 
{ 
	int rc, i=1;
	int *arg;

	DBGpthread_mutex_init(&mutex, NULL, "mutex_init fail\n");

	while (1) {
		printf("Main dentro al while\n"); fflush(stdout);
		pthread_t *tid = (pthread_t*)malloc(sizeof(pthread_t));
		arg = (int*)malloc(sizeof(int));
		*arg = i;

		DBGpthread_mutex_lock(&mutex, "[main] mutex_lock fail\n");
		if (nThreadsAlive < MAXNUMTHREAD) {
			rc = pthread_create(tid, NULL, rabbit, (void*)arg);
			if (rc != 0) printf("[main] pthread_create fail\n");
			else nThreadsAlive++;
		}
		DBGpthread_mutex_unlock(&mutex, "[main] mutex_unlock fail\n");

		i++;
		printf("Main aspetta...\n"); fflush(stdout);
		sleep(DELAYNEWRABBIT);
	}

	pthread_exit(NULL);
	return(0); 
} 
  
