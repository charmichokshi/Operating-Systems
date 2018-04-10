#include <sys/types.h>
#include <unistd.h> /* for fork() */

main()
{
pid_t pid;	/*holds process-id in parent*/

printf("One\n");
pid=fork();
printf("Two\n");
}
