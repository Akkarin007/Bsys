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

	long long n = atoi(argv[1]);
	struct timespec start, end;
	long long result = 0;

	for(int i = 0; i < n; ++i){
		clock_gettime(CLOCK_REALTIME, &start);
		read(0,NULL,0);
		clock_gettime(CLOCK_REALTIME, &end);
		result += (end.tv_nsec - start.tv_nsec);
	}


	printf("duration in nanoseconds: %lld\n", result/n);

return 0;
}
