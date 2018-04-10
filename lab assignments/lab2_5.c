#include<stdio.h>

void main(void)
{
    int id;
    id=fork();

    if(id>0)
    {
	printf("Sleep mode on...\n");
    	sleep(6);
	
    }
    if(id==0)
	{
        printf("I am zombiee child\n");		
        sleep(4);	//when the process become zombie
		printf("Sleep Finished\n");
	}
}
