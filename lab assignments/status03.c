#include <sys/types.h>
#include <sys/wait.h> /* for wait() */
#include <unistd.h> /* for fork() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for perror() */

int main(void)
{
int fatal(char *);
pid_t pid;
int status, exit_status;

if ((pid = fork()) < 0)
	fatal("fork failed");

/* Parent Process waiting for child process */

printf("\nPID: %d: \n", pid);

while (waitpid(pid, &status, WNOHANG) == 0)
{
	printf("Still waiting...\n");
	sleep(1);
}

/* to test to see how the child process was terminated */
if (WIFEXITED(status))
{
	exit_status = WEXITSTATUS(status);
	printf("Exit status from %d was %d\n",pid, exit_status);
}

if (pid==0)
	/* child process call the library routine sleep to suspend execution for few seconds*/
	printf("\nChild Process ID %d is sleeping...\n", getpid());
	sleep(3);
	exit(5);	/* exit with non-zero value */
}
int fatal(char *s)
{
	perror(s);
	exit(1);
}
