#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

 
int main ()
{
 int a;
 pid_t pid;
 printf ("\nRunning in main process with Process ID : %d",getpid());
 
 pid = fork ();         
 wait(&a);
 if (pid>0)                             //The parent process will have non zero positive PID
   {
     printf ("\nParent process running with PID %d ",getpid ());
     printf ("\nIt's child's PID is %d", pid);
     printf ("\n");   
}
 if(pid==0)                                   // child process will have PID 0
   {
     printf ("\nThe child process running with PID %d and PPID %d.",getpid (), getppid ());
     printf ("\n");
   }
 printf ("\nThe process with PID %d will be terminated\n", getpid () );                    //printed two times one in parent and one in child
 return 0;
}



