#include <sys/types.h>
#include <sys/wait.h> /* for wait() */
#include <unistd.h> /* for fork() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for perror() */

void main(void)
{
int fatal(char *);
pid_t pid;
int status, exit_status;

if ((pid = fork()) < 0)
	fatal("fork failed");

/* Parent Process waiting for child process */

printf("\nPID: %d: \n", pid);

if ((pid = wait(&status)) == -1)
{
	perror("wait failed");
	exit(2);
}
/* test to see how the child process was terminated */
	printf("\nStatus %d :\n", status);

if (WIFEXITED(status))
{
	exit_status = WEXITSTATUS(status);
	printf("Exit status from %d was %d\n", pid, exit_status);
}
exit(0);

if (pid==0)
	/* child process call the library routine sleep to suspend execution for 9 seconds*/
{	printf("\nChild Process\n");
	sleep(3);
//	exit(5);	/* exit with non-zero value */
}


}

int fatal(char *s)
{
	perror(s);
	exit(1);
}
