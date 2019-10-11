 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/wait.h>

int main(void) {
	int fd = open("./task02.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	char *buf1 = "I am parent\n";
	char *buf2 = "I am child\n";
   	
	if (fd == -1) {
		perror("file could not be opened");
		exit(1);
	}

	int rc = fork();
   	if (rc < 0) {
       		// fork failed
       		fprintf(stderr, "fork failed\n");
       		exit(1);
   	} else if (rc == 0) {
       		write(fd, buf1, strlen(buf1));
       	} else {
		write(fd, buf2, strlen(buf2));
	}
	return 0;
}

