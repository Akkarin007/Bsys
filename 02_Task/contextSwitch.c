#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

int main(int argc, char ** argv) {

if(argc != 4){
	printf("arguments are too less or too much");
	return 1;
}


cpu_set_t set;

int parentCPU = atoi(argv[1]);
int childCPU = atoi(argv[2]);
int iteration = atoi(argv[3]);
char string[80] = "text";
char text[80];



struct timespec start, end;
//int result = 0;

CPU_ZERO(&set);
int pipe1[2];
int pipe2[2];

pipe(pipe1);
pipe(pipe2);

int ret = fork();

if(ret == -1){
	perror("fork failed");
	exit(1);
}

if (ret == 0) {
	printf("I am his child\n");

	CPU_SET(childCPU, &set);
        sched_setaffinity(getpid(), sizeof(set), &set);

	close(pipe2[1]); //close pipe2 output
	close(pipe1[0]); //close pipe1 input

	for(int i = 0; i < iteration; ++i){
	//write to parent through pipe1
									printf("2\n");
	write(pipe1[1], string, strlen(string)+1);
									printf("3\n");
	clock_gettime(CLOCK_REALTIME, &end);
	printf("end Time!: %ld\n", end.tv_sec*100000000 + end.tv_nsec);
	//read from parent through pipe2 -----------------------------
	read(pipe2[0], text, strlen(string)+1);
	}
	exit(0);

} else { // parent
	printf("I am a parent\n");

	CPU_SET(parentCPU, &set);
 	sched_setaffinity(getpid(), sizeof(set), &set);
	close(pipe1[1]); //close pipe1 output
	close(pipe2[0]); //close pipe2 input

	while(1){
	//read from child through pipe1 ------------------------------

	clock_gettime(CLOCK_REALTIME, &start);
	printf("start!: %ld\n", end.tv_sec*100000000 + end.tv_nsec);
									printf("1\n");
	read(pipe1[0], text, strlen(string)+1);
									printf("4\n");
	//write to child through pipe2
	write(pipe2[1], string, strlen(string)+1);
									printf("5\n");
	}

	wait(NULL); //wait for child, so process shutdowns

}
return 0;
}
