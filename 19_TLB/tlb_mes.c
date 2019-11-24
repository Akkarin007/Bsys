#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>

int meassurement(int,int,int);

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Please restart with %s num-of-pages num-of-trials\n", argv[0]);
		exit(1);
	}

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	sched_setaffinity(getpid(), sizeof(set), &set);

	int PAGESIZE = getpagesize();
	int NUMPAGES = atoi(argv[1]);
	int NUMTRIALS = atoi(argv[2]);
	int jump = PAGESIZE / sizeof(int); //1024



	int time = meassurement(NUMPAGES, NUMTRIALS, jump);

	printf("%d %d\n", NUMPAGES, time);

	return 0;
}

int meassurement(int NUMPAGES, int NUMTRIALS, int jump){


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

	int *a = (int*) calloc(NUMPAGES * jump, sizeof(int));
	if(a == NULL){
		perror("Alloc failed a");
	}
	int *times = (int*) calloc(NUMPAGES * jump, sizeof(int));
	if(times == NULL){
		perror("Alloc failed a");
		free(a);
	}


	unsigned long sum = 0;


	for (int j = 0; j < NUMTRIALS; j++)
	{
		for (int i = 0; i < NUMPAGES * jump; i += jump)
		{
	  	clock_gettime(CLOCK_REALTIME, &start);
	   	a[i] += 1;
	  	clock_gettime(CLOCK_REALTIME, &end);
	  	times[i] = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec) - precision;
		sum += times[i];
	//	printf("%d -> %d\n", i, times[i]);
		}
	}

	free(times);
	free(a);
	return sum / (NUMPAGES * NUMTRIALS); 
}
