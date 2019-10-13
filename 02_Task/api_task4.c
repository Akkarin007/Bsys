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
	printf("hello, I am child (pid:%d)\n", (int) getpid());

 	// now exec "wc"...
	char *myargs[3];
	myargs[0] = strdup("/bin/ls"); // program: wc (word count)
	myargs[1] = NULL; // arg: file to count
	execvp(myargs[0], myargs); // runs word count
} else {
	// parent goes down this path (main)
	int rc_wait = wait(NULL);
	printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
}
return 0;
}
