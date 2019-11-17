 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/wait.h>

int main(void) {



int rc = fork();
	if (rc < 0) {
	// fork failed
	fprintf(stderr, "fork failed\n");
	exit(1);
	} else if (rc == 0) {
		// child: redirect standard output to a file
		printf("(hallo) hello, I am child (pid:%d)\n", (int) getpid());
	} else {
		sleep(1);
		// parent goes down this path (main)
		printf("(goodbye) hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
	}
	return 0;
}
