#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include "handoverlist.h"


typedef struct threadargs
{
    list *liste;
    int data;
    int anzahl;
} threadargs;

void *hinzufuegen(void *argsT)
{
	threadargs *args = (threadargs *) argsT;
	int i;
	for(i = 0; i < args->anzahl; i++)
	{
		add(args->liste,args->data);
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

	//cpu_set_t set;
	//CPU_ZERO(&set);
	//CPU_SET(0, &set);
	//sched_setaffinity(getpid(), sizeof(set), &set);

    int anzahl = atoi(argv[1]);
    int loops = atoi(argv[2]);

    pthread_t threads[anzahl];
    int zeitMessung;
    int messung;

    threadargs argsT[anzahl];
    list liste;
    init(&liste);

    long zeit[anzahl];

    struct timespec start,end;

    clock_gettime(CLOCK_REALTIME, &start);

    int i;
    for(i = 0; i < anzahl; i++)
    {
        argsT[i].liste = &liste;
		argsT[i].data = i*i;
		argsT[i].anzahl = loops;
		pthread_create(&threads[i], NULL, hinzufuegen, &argsT[i]);
    }
    for(i = 0; i < anzahl; i++)
    {
       pthread_join(threads[i], (void**) &zeit[i]);
    }
    clock_gettime(CLOCK_REALTIME, &end);

    zeitMessung = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec)-getPrecision();

    printf("%d\n", zeitMessung);
    return 0;
}
