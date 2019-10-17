#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char ** argv) {


	if(argc !=2){
	fprintf(stderr, "Aufruf: %s Integer Wert", argv[0]);
	}

	printf("helloMechanismTask4.c:\n");
	printf("	My PID %d.\n", getpid());

	long n = atoi(argv[1]);
	struct timespec start, end, start2, end2, test;
	long result = 0;	long first = 0;
	long second = 0;
	long *start;
	long *second;
	int i = -1;

	for(int i = 0; i < n; ++i){
		clock_gettime(CLOCK_REALTIME, &start);
		getpid();
		clock_gettime(CLOCK_REALTIME, &end)
		first[++i] = start ;
	}
	clock_gettime(CLOCK_REALTIME, &end);

	
	for(int i = 0; i < 100; ++i){
		clock_gettime(CLOCK_REALTIME, &start2);
		clock_gettime(CLOCK_REALTIME, &test);
		clock_gettime(CLOCK_REALTIME, &end2);
		second += (end2.tv_sec - start2.tv_sec)*1000000000 + end2.tv_nsec - start2.tv_nsec;
	}

	long second = ;

	result = first - (second/100);

	printf("duration in nanoseconds: %ld\n", result/n);

return 0;
}
