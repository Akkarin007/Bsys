#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int * intPointer= NULL;
	printf("%d", *intPointer);
	return 0;
}
