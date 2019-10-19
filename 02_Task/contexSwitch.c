#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sched.h>


int main(void) {

cpu_set_t set;
int parentCPU, childCPU;

int pipe1[2];
int pipe2[2];
parentCPU = 0;
childCPU = 0;

char string[] = "Hello new Process!\n";
char readbuffer[80];
char string2[] = "my name is Isy";
CPU_ZERO(&set);


pipe(pipe1);
pipe(pipe2);
int ret = fork();


if(ret == -1){
	perror("fork failed");
	exit(1);
}

if (ret == 0) {
	CPU_SET(childCPU, &set);
        sched_setaffinity(getpid(), sizeof(set), &set);


	//read from parent through pipe1
	close(pipe1[1]); //close output
	read(pipe1[0], readbuffer, sizeof(string)+1);
	printf("Received string: %s", readbuffer);


	//write to parent through pipe2
	close(pipe2[0]);
	write(pipe2[1], string2, strlen(string2)+1);

	exit(0);

} else { // parent

	CPU_SET(parentCPU, &set);
 	sched_setaffinity(getpid(), sizeof(set), &set);

	//write to child through pipe1
	close(pipe1[0]); //close input
	write(pipe1[1],string, strlen(string)+1);


	//read from child through pipe2
	char string3[80];
	close(pipe2[1]);
	read(pipe2[0], string3, sizeof(string2)+1);
	printf("Received string2 %s\n", string2); 

	wait(NULL); //wait for child, so process shutdowns

}
return 0;
}
