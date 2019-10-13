 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/wait.h>
 #include <sys/time.h>
 #include <errno.h>

 int main(int argc, char ** argv) {


	if(argc !=2){
	fprintf(stderr, "Aufruf: %s Integer Wert", argv[0]);
	}

	printf("helloMechanismTask4.c:\n");
	printf("	My PID %d.\n", getpid());

	int n = atoi(argv[1]);
	struct timeval start, end;

	gettimeofday(&start, NULL);

	for(int i = 0; i < n; ++i){
		open("./mechanism01.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	}

	gettimeofday(&end, NULL);


	printf("duration in milliseconds: %ld\n", (end.tv_usec - start.tv_usec));
	close(STDOUT_FILENO);
 return 0;
}
