#include <stdio.h> /* for printf() */

void main(int argc, char **argv)
{
while(--argc > 0)

{
	printf("%s", *++argv);
	printf("\n");
}
}
