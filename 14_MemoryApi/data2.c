#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int *data = (int *) malloc(100 *sizeof(int));
	free(data);
	printf("test: %d\n", data[1]);
	return 0;
}
