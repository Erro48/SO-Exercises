#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define BANKS_NUM 3
#define DEPOSIT_THREAD_NUM 5
#define WITHDRAW_THREAD_NUM 4
#define START_DELAY 1000*1000		/* milliseconds */
#define FINAL_DELAY 200*1000
#define DELAY_BEFORE_EXIT_BDI 1000*1000
#define DELAY_BEFORE_LOOP_BDI 30000*1000

void initAll(int arr[], int value, int length);
void* depositThread(void* args);
void* withdrawThread(void* args);
void* bancaDItalia(void* args);

pthread_mutex_t mutex;

int T[BANKS_NUM];	/* total amount owned by a bank */
int N[BANKS_NUM];	/* number of operations done by a bank */

int main() {
	int i, j, errCre;
	int* val;
	pthread_t tid_bdi;
	initAll(T, 0, BANKS_NUM);
	initAll(N, 0, BANKS_NUM);
	errCre = pthread_create(&tid_bdi, NULL, bancaDItalia, NULL);
	if (errCre != 0) printf("[ERROR:BDI] code: %i\n", errCre);
	for (i = 0; i < BANKS_NUM; i++) {
		val = (int*)malloc(sizeof(int));
		*val = i;
		/* creation of deposit threads */
		pthread_t tid_dep[DEPOSIT_THREAD_NUM];
		for (j = 0; j < DEPOSIT_THREAD_NUM; j++) {
			errCre = pthread_create(&tid_dep[j], NULL, depositThread, (void*)val);
			if (errCre != 0) printf("[ERROR:D] code: %i\n", errCre);
		}

		/* creation of withdraw threads */
		pthread_t tid_wit[WITHDRAW_THREAD_NUM];
		for (j = 0; j < WITHDRAW_THREAD_NUM; j++) {
			errCre = pthread_create(&tid_wit[j], NULL, withdrawThread, (void*)val);
			if (errCre != 0) printf("[ERROR:W] code: %i\n", errCre);
		}
	}
	pthread_exit(0);
	return 0;
}

void initAll(int arr[], int value, int length) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = value;
	}
}

void * depositThread(void* args) {
	int val = *((int*)args);
	free(args);
	int i;
	while (1) {
		usleep(START_DELAY);
		/* sezione critica */
		pthread_mutex_lock(&mutex);
		T[val] += 10;
		N[val]++;
		usleep(FINAL_DELAY);
		pthread_mutex_unlock(&mutex);
	}
	free(val);
	pthread_exit(NULL);
}

void * withdrawThread(void* args) {
	int val = *((int*)args);
	int i;
	free(args);
	while (1) {
		usleep(START_DELAY);
		/* sezione critica */
		pthread_mutex_lock(&mutex);
		T[val] -= 9;
		N[val]++;
		usleep(FINAL_DELAY);
		pthread_mutex_unlock(&mutex);
	}
	free(val);
	pthread_exit(NULL);
}

void * bancaDItalia(void* args) {
	int i;
	while (1) {
		pthread_mutex_lock(&mutex);
		for (i = 0; i < BANKS_NUM; i++) {
			printf("Bank n° %i: T=%i\tN=%i\n", i, T[i], N[i]);
		}
		usleep(DELAY_BEFORE_EXIT_BDI);
		pthread_mutex_unlock(&mutex);
		usleep(DELAY_BEFORE_LOOP_BDI);
	}
	pthread_exit(NULL);
}
