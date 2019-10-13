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

	if(clock_gettime(CLOCK_REALTIME, &start) == -1){
	perror("time error");
	return 1;
	}

	for(int i = 0; i < n; ++i){
		read(0,NULL,0);
	}

        if(clock_gettime(CLOCK_REALTIME, &end) == -1){
        perror("time error");
        return 1;
        }


	printf("duration in nanoseconds: %lld\n", (end.tv_nsec - start.tv_nsec)/n);

 return 0;
}
