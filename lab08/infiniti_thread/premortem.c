#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define TIMEDELAY 1000	/* microseconds */

typedef struct tstruct {
	int index;
	pthread_t id;
} tstruct;

void* threadBody(void* arg) {
	tstruct* data;
	data = (tstruct*)arg;
	printf("[THREAD] %i\n", data->index);
	usleep(TIMEDELAY);
	pthread_t tid;
	data->index++;
	pthread_create(&tid,NULL,threadBody,(void*)data);
	pthread_join(data->id,NULL);
}

int main() {
	int index = 0;
	usleep(TIMEDELAY);
	pthread_t tid;
	tstruct* data;
	data = (tstruct*)malloc(sizeof(tstruct));
	data->index++;
	data->id = pthread_self();

	pthread_create(&tid,NULL,threadBody,(void*)data);
	return(0);
}
