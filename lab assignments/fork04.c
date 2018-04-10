#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int index;
	for (index = 1; index < 4; index++)
		fork();
	printf("Unix System Programming\n");
	exit(0);
}
