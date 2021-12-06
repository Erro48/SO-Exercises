/* file:  piattello.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE     /* per random e srandom */
#endif


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>     /* random  srandom */
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMTIRATORI 10
#define TEMPOVOLO 3
#define DELAYTRADUEPIATTELLI8sec 8

/* dati da proteggere - AGGIUNGETE QUELLO CHE VI SERVE */
int piattelloVivo;


/* variabili per la sincronizzazione - AGGIUNGETE QUELLO CHE VI SERVE */
pthread_mutex_t mutex;
pthread_cond_t condPiattelloPartito, condPiattelloArrivato;

void attendi( int min, int max) {
	int secrandom=0;
	if( min > max ) return;
	else if ( min == max ) 
		secrandom = min;
	else
		secrandom = min + ( random()%(max-min+1) );
	do {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 ) 
			{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	} while( secrandom>0 );
	return;
}

void *Tiratore (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Tiratore%" PRIiPTR "",indice);

	/*  da completare  */

	while ( 1 ) {


		/*  da completare  */


		/* il tiratore  attende l'inizio del volo del piattello */
		printf("tiratore %s attende piattello \n", Plabel);
	        fflush(stdout);

		/*  da completare  */
		DBGpthread_mutex_lock(&mutex, NULL);
		/* aspetta che il piattello parta  */
		DBGpthread_cond_wait(&condPiattelloPartito, &mutex, NULL);
		DBGpthread_mutex_unlock(&mutex, NULL);

		printf("tiratore %s mira e .... \n", Plabel);
	        fflush(stdout);

		/*  da completare  */


		/* il tiratore si prepara a sparare impiegando da 2 a 4 secondi */
		attendi( 2, 4 );


		/*  da completare  */
		DBGpthread_mutex_lock(&mutex, NULL);

		if(piattelloVivo) {
			/* colpisco il piattello */
			printf("tiratore %s HA COLPITOOOOOOOOOOOOOOOO\n", Plabel);
			fflush(stdout);
		} else {
			/* piattello caduto o colpito da qualcun altro */
			printf("tiratore %s urla di rabbia\n", Plabel);
			fflush(stdout);
		}

		DBGpthread_mutex_unlock(&mutex, NULL);


		/* il tiratore finisce il tentativo di sparare al piattello in volo */
/*		printf("tiratore %s ha sparato o e' arrivato tardi\n", Plabel);
	        fflush(stdout);*/


		/*  da completare  */


	}
	pthread_exit(NULL); 
}


void *Piattello (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Piattello%" PRIiPTR "",indice);


	/*  da completare  */

	printf("piattelo %s inizia volo\n", Plabel);
        fflush(stdout);

	/*  da completare  */
	DBGpthread_mutex_lock(&mutex, NULL);
	piattelloVivo = 1;
	/* il piattello avvisa che è partito */
	DBGpthread_cond_broadcast(&condPiattelloPartito, NULL);
	DBGpthread_mutex_unlock(&mutex, NULL);

	/* il piattello vola per tre secondi */
	attendi( TEMPOVOLO, TEMPOVOLO );


	/*  da completare  */


/*	printf("piattelo %s finisce volo e termina\n", Plabel);
      	fflush(stdout);*/

	/*  da completare  */
	DBGpthread_mutex_lock(&mutex, NULL);
	if(piattelloVivo) {
		piattelloVivo = 0;
		printf("piattello %s caduto\n", Plabel);
		fflush(stdout);
	} else {
		printf("piattello %s colpito\n", Plabel);
		fflush(stdout);
	}
	DBGpthread_mutex_unlock(&mutex, NULL);

	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	uintptr_t i=0;
	int seme;
	/* aggiungete eventuali vostre variabili */
	pthread_t thp;

	seme=time(NULL);
        srandom(seme);

	/* INIZIALIZZATE LE VOSTRE VARIABILI CONDIVISE e tutto quel che serve - fate voi */
	DBGpthread_cond_init(&condPiattelloPartito, NULL, NULL);
	DBGpthread_cond_init(&condPiattelloArrivato, NULL, NULL);
	DBGpthread_mutex_init(&mutex, NULL, NULL);

	/* all'inizio non c'e' nessun piattello in volo */


	/* CREAZIONE PTHREAD dei tiratori */
	for(i=0;i<NUMTIRATORI;i++) {
		rc=pthread_create(&th,NULL,Tiratore,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* CREAZIONE NUOVO PIATTELLO OGNI 8 secondi */
	i=0;
	while(1) {
			/* un nuovo piattello ogni 8 secondi */
			attendi( DELAYTRADUEPIATTELLI8sec, DELAYTRADUEPIATTELLI8sec );
			i++;

			/* crea pthread piattello - completate voi */
			rc = pthread_create(&thp, NULL, Piattello, (void*)i);
			if(rc) PrintERROR_andExit(rc, "pthread_create failed");

			printf("\n\n"); fflush(stdout);
	}

	pthread_exit(NULL);
	return(0); 
} 
  
