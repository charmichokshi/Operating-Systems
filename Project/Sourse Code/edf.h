//Program - Header file for implementation of earliest deadline first scheduling algorithm
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <math.h>

int ProcessNo;
int ExecTime[1000];
int Deadline[1000];
int Period[1000];
int LCM_Period;

char help[255];
int i,j,h;
float f;
int deadlock_cnt = 0;
int deadlock_a[1];

void interrupt_sig_handler(int sigval)
{
    printf("\n\nInterrupt Signal Caught: %d", sigval);
    printf("\nInterrupt Disabled\n");
}

void getProcesses()
{
    FILE *InputFile;
    InputFile =fopen("/home/charmi/Desktop/OS PROJECT/input/input_edf.txt","r");

    if (InputFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    else
    {
        fgets(help, 255, InputFile);
        ProcessNo =atoi(help);

        for(i=0; i<ProcessNo; i++)
        {
            fgets(help, 255, InputFile);
            ExecTime[i]=atoi(help);

            fgets(help, 255, InputFile);
            Deadline[i]=atoi(help);

            fgets(help, 255, InputFile);
            Period[i]=atoi(help);

        }
        fclose(InputFile);
        //showing the process;
        printf("\nInput Data\n\n");
        printf("Pi |Ci, Di, pi\n");
        printf("---------------\n");
        for(i=0;i<ProcessNo;i++)
        {
            printf("P%d | %d, %d, %d\n",i+1,ExecTime[i], Deadline[i],Period[i]);
        }
        printf("\n");
    }

}

void getPeriodLCM()
{
    int help[1000];
    for(i=0; i<ProcessNo; i++)
    {
        help[i]=Period[i];
    }
    int h=0;
    int lh;
    int li;
    while(h==0)
    {
        h=1;
        lh = help[0];
        li=0;

        for(i=0; i<ProcessNo; i++)
        {
            if(lh!=help[i])
            {
                h=0;
                if(lh>help[i])
                {
                    lh=help[i];
                    li=i;
                }
            }
        }
        if(h==0)
        {
            help[li]=lh+Period[li];
        }
    }
    LCM_Period=help[0];
    printf("\nLCM: %d",LCM_Period);
    printf("\nWe can schedule the real system in %d units.\n",LCM_Period);
}

void sig_div_zero_handler() 
{
    printf("\nSiganl Generated: Dovision by 0\n");

    printf("\nThis Real time system is not schedulable\n");
    FILE *OutputFile;
    OutputFile = fopen("/home/charmi/Desktop/OS PROJECT/output/output_edf.txt","w");
    fprintf(OutputFile,"This Real time system is not schedulable");
    fclose(OutputFile);

    print_menu();
}

float schedulability()
{        
    signal(SIGFPE, sig_div_zero_handler);

    float condition=0, c=0;
    float x,y;
    int a=0,b=0,d=0;

    for(i=0;i<ProcessNo;i++)
    {
        x=ExecTime[i];
        y=Period[i];

        a=ExecTime[i];
        b=Period[i];

        d= a/b;   //signal will generate from here
        c =x/y;

        condition = condition + c;
    }

    printf("CPU Utilization: ");
    printf("%f",condition);
    return condition;
}

void schedule()
{
    FILE* OutputFile=NULL;

    OutputFile = fopen("/home/charmi/Desktop/OS PROJECT/output/output_edf.txt", "w");
     truncate("/home/charmi/Desktop/OS PROJECT/output/output_efd.txt", 0);

    //the closest deadline
     int earlyDeadline;
     //the closest deadline index
     int index;
     //the table of scheduling
     int schedulingtable[LCM_Period];
     //the table holds the remaining execution time for each process
     int remainsCapacity[1000];
    //the table holds the number between the current time and next deadline for each process
     int nextDeadline[1000];
     //the table holds the current time in the current period
     int OnlineNewPeriod[1000];

     fprintf(OutputFile,"Periods LCM = %d\n",LCM_Period);

    for(i=0; i<ProcessNo; i++)
    {
     nextDeadline[i]=Deadline[i];
     remainsCapacity[i]=ExecTime[i];
     OnlineNewPeriod[i]=0;
    }

    // fprintf(OutputFile,"Periods LCM = %d\n",LCM_Period);
    printf("\n");
    printf("Time    PID\n");
    printf("-----------\n");
    for(i=0;i<LCM_Period;i++)
    {
         earlyDeadline = LCM_Period;
         index = -1;
         for(j=0;j<ProcessNo;j++)
         {
                 if(remainsCapacity[j]>0)
                 {
                     if(earlyDeadline>nextDeadline[j])
                     {
                         earlyDeadline=nextDeadline[j];
                         index=j;

                         if (deadlock_cnt>1)
                         {
                              printf("\nDeadlock Avoided...");
                              printf("\nP%d allocated to CPU, based on selection of nearest deadline\n", index+1);
                         }
                        
                     }

                 }
         }

        signal(SIGINT, interrupt_sig_handler);  //ctrl+c
        signal(SIGTSTP, interrupt_sig_handler); //ctrl+z
        sleep(1);

        printf("\n(%d,%d):",i,i+1);
        printf("  P%d",index+1);
             
             fprintf(OutputFile, "(%d,%d): P%d\n",i,i+1,index);
             remainsCapacity[index]=remainsCapacity[index]-1;

             deadlock_cnt=0;

             for(j=0; j<ProcessNo; j++)
             {
                if(OnlineNewPeriod[j]==(Period[j]-1))
                {
                    //execute this part when any process arrives, if 2 processes arrievs then, 
                        //this will execute 2 times
                        nextDeadline[j]=Deadline[j];
                        remainsCapacity[j]=ExecTime[j];
                        OnlineNewPeriod[j]=0;

                        // printf("hi\n");
                        

                        deadlock_cnt++;

                        if (deadlock_cnt == 1)
                        {
                            deadlock_a[0] = j+1;
                        }

                        if (deadlock_cnt == 2)
                        {
                            printf("\n\n...Deadlock Detected...");
                            printf("\nFollowing Processes accured at same time: \n");
                            printf("P%d\nP%d\n",deadlock_a[0], j+1 );
                        }
                        else if(deadlock_cnt > 2)
                        {
                            printf("P%d\n",j+1 );
                        }     
                }
                
                else
                {
                    if(nextDeadline[j]>0)
                    {
                        nextDeadline[j]--;
                    }
                    else
                    {
                        if(remainsCapacity[j]>0)
                        {
                            printf("\n The process %d has no chance to complete its capacity",j);
                            fprintf(OutputFile,"\n the process %d has no chance to complete its capacity",j);
                        }
                    }
                    OnlineNewPeriod[j]=OnlineNewPeriod[j]+1;
                }    
            }
    }

    fclose(OutputFile);
}

void edf()
{

    system("clear");

    puts("EARLIEST DEADLINE FIRST ALGORITHM");
    puts("=================================");
    //for()

    getProcesses();

    f=schedulability();

    if(f<=1)
    {
        printf("\nThis Real time system is schedulable because %f <= 1\n",f);
        // printf("LCM \n");
        getPeriodLCM();
        
        schedule();
        printf("\n");
    }
    else{
         printf("\nThis Real time system is not schedulable because %f >1\n",f);
         FILE *OutputFile;
         OutputFile = fopen("/home/charmi/Desktop/OS PROJECT/output/output_edf.txt","w");
         fprintf(OutputFile,"This Real time system is not schedulable because %f >1",f);
         fclose(OutputFile);
         // exit(0);
    }
}
