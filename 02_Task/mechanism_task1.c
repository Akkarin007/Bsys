#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char ** argv) {


	if(argc !=2){
	fprintf(stderr, "Aufruf: %s Integer Wert", argv[0]);
	}

	long n = atoi(argv[1]);
	struct timespec start, end, test;
	unsigned long midTimeResult = 0;



	for(int i = 0; i < n; ++i){
		clock_gettime(CLOCK_REALTIME, &start);
		read(0,NULL,0);
		clock_gettime(CLOCK_REALTIME, &end);
		midTimeResult += (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec ;
	}
	clock_gettime(CLOCK_REALTIME, &start);

	for(int i = 0; i < n; ++i){
		clock_gettime(CLOCK_REALTIME, &test);
		clock_gettime(CLOCK_REALTIME, &test);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	midTimeResult -= (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec ;


	int result = midTimeResult / n;

	printf("%d", result);

return 0;
}
