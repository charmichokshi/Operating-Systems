#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define N 5

int main()
{
int status, i;
pid_t pid;
for (i = 0; i < N; i++)
	if ((pid = fork()) == 0) /* Child */
	exit(100+i);

/* Parent waits for all of its children to terminate */
while ((pid = waitpid(-1, &status, 0)) > 0) 
	{
	if (WIFEXITED(status))
		printf("child %d terminated normally with exit status =%d\n", pid, WEXITSTATUS(status));
	else
		printf("child %d terminated abnormally\n", pid);
	}

if (errno != ECHILD)
	printf("waitpid error");

exit(0);
}
