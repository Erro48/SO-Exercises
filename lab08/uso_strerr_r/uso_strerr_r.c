#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int main() {
	int joinRes, interrRes;
	void *p;
	char strerrRes[100];
	
	joinRes = pthread_join(pthread_self(), &p);
	printf("join restituisce %i\n", joinRes);
	interrRes = strerror_r(joinRes, strerrRes, 100);
	if (interrRes != 0) {
		printf("strerror_r failed: errore %i\n", interrRes);
	}
	printf("L'esito della stampa è: %i %s\n", interrRes, strerrRes);

	return 0;
}
