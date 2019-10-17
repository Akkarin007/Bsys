#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sched.h>



int main(void) {
int fd[2];
pid_t childpid;
char string[] = "Hello new Process!\n";
char readbuffer[80];

pipe(fd);
if((childpid = fork()) == -1){
	perror("fork");
	exit(1);
}

if (childpid == 0) {
	// child: redirect standard output to a file
	close(fd[1]); //close output
	read(fd[0], readbuffer, sizeof(string)+1);
	printf("Received string: %s", readbuffer);
	exit(0);
} else { // parent
	close(fd[0]); //close input
	write(fd[1],string, strlen(string)+1);
	wait(0); //wait for child, so process shutdowns
}
return 0;
}
