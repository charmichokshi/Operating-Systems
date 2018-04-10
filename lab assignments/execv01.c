#include <sys/types.h>
#include <unistd.h> /* for fork() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for perror() */

void main(void)
{
char * const av[]={"ls","-la",(char *)0};

execv("/bin/ls", av);

/* If execv returns back, the call has failed... */
perror("execv could not run ls");
exit(1);
}
