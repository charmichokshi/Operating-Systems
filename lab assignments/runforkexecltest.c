#include <sys/types.h>
#include <sys/wait.h> /* for wait() */
#include <unistd.h> /* for fork() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for perror() */

int main(void)
{
int fatal(char *);
pid_t pid;

printf("PID before fork, ie PID of current process: %d\n", getpid());
switch(pid = fork())
{
case -1:
	fatal("fork failed");
	break;
case 0:
	/* child process calls exec */
	printf("Message from a Child Process\n");
	printf("\n");
	printf("The Value PID assigned by pid-t and known to a Child Process : %d\n", pid);
	printf("The value of PID of child process: %d\n", getpid());
	printf("The value of Parent PID, who created me: %d\n", getppid());
	
	execl("/bin/ls", "ls", "-l", (char *)0);
	printf("\n");

	fatal("exec failed");
	break;
default:
	/* parent process uses wait to suspend execution
	* until child process finishes */
	wait((int *)0);
	printf("Message from a parent process\n");	
	printf("PID of child known to the parent: %d\n", pid);
	printf("TASK ACCOMPLISHED, ie. We are back from MOON \n");
	exit(0);
}
}
int fatal(char *s)
{
	perror(s);
	exit(1);
}
