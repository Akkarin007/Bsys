 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/wait.h>

//int favNum = 42; if the other file had the similar var this one would be reinitialized by executing exec()

 int main(void) {
	printf("helloApiTask4.c:\n");
	printf("	My PID %d.\n", getpid());

 int rc = fork();
 if (rc < 0) {
 	// fork failed
 	fprintf(stderr, "fork failed\n");
 	exit(1);
 } else if (rc == 0) {
	printf("hello, I am child (pid:%d)\n", (int) getpid());
	printf("---->");

 	// now exec "wc"...
	char *myargs[3];
	myargs[0] = strdup("/bin/ls"); // program: ls command
	myargs[1] = "-l"; // arg: list all files
	myargs[2] = NULL; // end of arguments/file

	//With L: comma separated arguments
	//execl(myargs[0], "-l",NULL);
	//With V: Vector (i.e., an array of strings)
	//execv(myargs[0], myargs); 
	//With P: Include normal search path for execitable
	execvp(myargs[0],myargs); //runs ls -l command
} else {
	// parent goes down this path (main)
	int rc_wait = wait(NULL);
	printf("hello, I am parent of %d (rc_wait: %d) (pid:%d)\n", rc, rc_wait, (int) getpid());
}
printf("i am executed :D\n");
return 0;
}
