#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int x = 69;
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		x = 42;
		printf("pid is %d and my value is %d\n", getpid(), x);
	} else {
		x = 100;
		printf("pid is %d and my value is %d\n", getpid(), x);
	}

	printf("final value is %d\n", x);
	return 0;
}
