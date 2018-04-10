#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	fork();
	printf("Unix System Programming\n");
	exit(0);
}
