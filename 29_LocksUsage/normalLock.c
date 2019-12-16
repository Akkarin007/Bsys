#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include "counter.h"

typedef struct threadargs
{
    counter *zaehler;
    int anzahl;
} threadargs;

void *task(void *argsT)
{
    threadargs *args = (threadargs *) argsT;
    int i;

    for(i = 0; i <= args->anzahl; i++)
    {
        increment(args->zaehler);
    }
    return NULL;
}


unsigned long getPrecision(void){


	struct timespec start,end;

	unsigned long precision = 0;
	unsigned int precisionFaktor = 10000000;

	for (unsigned int i = 0; i < precisionFaktor; i++){
	  	clock_gettime(CLOCK_REALTIME, &start);
	  	clock_gettime(CLOCK_REALTIME, &end);
	  	precision += (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
	}
	precision /= precisionFaktor;
	//printf("precision: %ld\n", precision);

	return precision; 
}

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Please restart");
		exit(1);
	}

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	sched_setaffinity(getpid(), sizeof(set), &set);

	
    pthread_t threads[anzahl];
    double zeitMessung;
    int messung;
    counter zaehler;
    init(&zaehler);
    threadargs arguments;
    arguments.zaehler = &zaehler;
    arguments.anzahl = loops;
    struct timeval start, ende;
    long zeit[anzahl];

    messung = gettimeofday(&start, NULL);
    if(messung != 0)
    {
        fprintf(stderr, "Fehlerhafte Zeit!");
        return 1;
    }

    int i;
    for(i = 0; i < anzahl; i++)
    {
       pthread_create(&threads[i], NULL, task, &arguments);
    }
    for(i = 0; i < anzahl; i++)
    {
       pthread_join(threads[i], (void**) &zeit[i]);
    }
    messung = gettimeofday(&ende, NULL);
    if(messung != 0)
    {
        fprintf(stderr, "Fehlerhafte Zeit!");
        return 1;
    }

    zeitMessung = (ende.tv_sec - start.tv_sec) * 1000000 + ende.tv_usec - start.tv_usec - getPrecision();

    printf("%f\n", zeitMessung);
    return 0;
}

