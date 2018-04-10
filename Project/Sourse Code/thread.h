//Program - This header file generates four thread to compare four scheduling algorithm
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
  int id;
  int sleep_time;
} parm;

#define MAX_THREADS 4

void *t_1(void *arg)
{
  fcfs_file_ip();
}

void *t_2(void *arg)
{
  rr_file_ip();
}

void *t_3(void *arg)
{
  sjf_file_ip();
}

void *t_4(void *arg)
{
    ps_file_ip();
}

void fn_thread() {

  int       i;
  int       sleep_time;
  pthread_t threads[MAX_THREADS];
  parm      p[MAX_THREADS];
  time_t    t1;
  int       ret;

  char help[501];
  FILE *InputFile = NULL;
  InputFile =fopen("/home/charmi/Desktop/OS PROJECT/output/starve_data.txt","r");
                 
  time(&t1);
  srand48((long) t1);

  printf("The process is generating %d threads.\n", MAX_THREADS);	

  for (i = 0; i < MAX_THREADS; i++) 
  {
   
    sleep_time = 1 + lrand48() % 3;
    p[i].id = i;
    p[i].sleep_time = sleep_time;
  }

    pthread_create(&threads[0], NULL, t_1, (void *)&p); 
    pthread_create(&threads[1], NULL, t_2, (void *)&p); 
    pthread_create(&threads[2], NULL, t_3, (void *)&p); 
    pthread_create(&threads[3], NULL, t_4, (void *)&p); 
 
  for (i = 0; i < MAX_THREADS; i++) 
  {
    pthread_join(threads[i], NULL);
  }


    if (InputFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    else
    {
        printf("Starvation analysis of each Algorithm:\n");

        for(i=0; i<5; i++)
        {
            fgets(help, 500, InputFile);
            printf("%s",help);
        }
        printf("\n");
    }

}
