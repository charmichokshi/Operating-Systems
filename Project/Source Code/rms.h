//Program - Header file for implementation of Rate monotonic scheduling algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ProcessNo;
int ExecTime[1000];
int Period[1000];
int LCM_Period_rms;

char help[255];
int i,j,h;
float f;

int deadlock_c = 0;
int deadlock_arr[1];

void interrupt_sig_handler_rms(int sigval)
{
    printf("\n\nInterrupt Signal Caught: %d", sigval);
    printf("\nInterrupt Disabled\n");
}

void getProcesses_rms()
{
    FILE *InputFile;
    InputFile =fopen("/home/charmi/Desktop/OS PROJECT/input/input_rms.txt","r");

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
            Period[i]=atoi(help);
        }
        fclose(InputFile);
        //showing the process;
        printf("\nInput Data\n\n");
        printf("Pi |Ci, pi\n");
        printf("-----------\n");
        for(i=0;i<ProcessNo;i++)
        {
            printf("P%d | %d, %d\n",i+1,ExecTime[i],Period[i]);
        }
        printf("\n");
    }

}

void getPeriodLCM_rms()
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
    LCM_Period_rms=help[0];
    printf("\nLCM: %d",LCM_Period_rms);
    printf("\nWe can schedule the real system in %d units.\n",LCM_Period_rms);


}

void sig_div_zero_handler_rms() 
{
    printf("\nSiganl Generated: Dovision by 0\n");

    printf("\nThis Real time system is not schedulable\n");
    FILE *OutputFile;
    OutputFile = fopen("/home/charmi/Desktop/OS PROJECT/output/output_rms.txt","w");
    fprintf(OutputFile,"This Real time system is not schedulable");
    fclose(OutputFile);

    print_menu();
}

int schedulability_rms()
{
    signal(SIGFPE, sig_div_zero_handler_rms);

    float ut,u,x,y;
    int c=0;

     //calculate the utilization
      for(i=0;i<ProcessNo;i++)
      {
        c=ExecTime[i]/ Period[i];
       x=(float)ExecTime[i]/(float)Period[i];
       ut+=x;
      }

      //calculate value of U
      y=(float)ProcessNo;
      y=y*((pow(2.0,1/y))-1);
      u=y;

      if(ut<u)
      {
        printf("CPU Utilization: %f",ut);
         printf("\nAs %f < %f ,",ut,u);
         printf(" The System is surely Schedulable.\n");
         return 1;
      }

     else
     {
        printf("\n Not Sure.....");
     return 0;
    }
}

void schedule_rms()
{
    FILE* OutputFile=NULL;

    OutputFile = fopen("/home/charmi/Desktop/OS PROJECT/output/output_rms.txt", "w");
     truncate("/home/charmi/Desktop/OS PROJECT/output/output_rms.txt", 0);

    //the closest arriving period
     int earlyRate;
     //the closest period index
     int index;
     //the table holds the remaining execution time for each process
     int remainsCapacity[1000];
    //the table holds the number between the current time and next period for each process
     int nextRate[1000];
     //the table holds the current time in the current period
     int OnlineNewPeriod[1000];

     fprintf(OutputFile,"Periods LCM = %d\n",LCM_Period_rms);

    for(i=0; i<ProcessNo; i++)
    {
     nextRate[i]=Period[i];
     remainsCapacity[i]=ExecTime[i];
     OnlineNewPeriod[i]=0;
    }

    printf("\n");
    printf("Time    PID\n");
    printf("-----------\n");
    for(i=0;i<LCM_Period_rms;i++)
    {
     earlyRate = LCM_Period_rms;
     index = 0;
     for(j=0;j<ProcessNo;j++)
     {
             if(remainsCapacity[j]>0)
             {
                 if(earlyRate>nextRate[j])
                 {
                     earlyRate=nextRate[j];
                     

                     if ((deadlock_c > 1) && (index < j))
                     {
                            index=j;
                          printf("\nDeadlock Avoided...");
                          printf("\nP%d allocated to CPU, based on selection of smallest period\n", index+1);
                     
                     }
                     index=j;
                 }
             }
    }

        signal(SIGINT, interrupt_sig_handler_rms);  //ctrl+c
        signal(SIGTSTP, interrupt_sig_handler_rms); //ctrl+z
        sleep(1);

         printf("\n(%d,%d):",i,i+1);
         printf("  P%d",index+1);

         fprintf(OutputFile, "\n(%d,%d): P%d",i,i+1,index);
         remainsCapacity[index]=remainsCapacity[index]-1;

         deadlock_c=0;

         for(j=0; j<ProcessNo; j++)
         {
            if(OnlineNewPeriod[j]==(Period[j]-1))
            {
                //execute this part when any process arrives, if 2 processes arrievs then, 
                    //this will execute 2 times
                    nextRate[j]=Period[j];
                    remainsCapacity[j]=ExecTime[j];
                    OnlineNewPeriod[j]=0;

                    deadlock_c++;

                    if (deadlock_c == 1)
                    {
                        deadlock_arr[0] = j+1;
                    }

                    if (deadlock_c == 2)
                    {
                        printf("\n\n...Deadlock Detected...");
                        printf("\nFollowing Processes accured at same time: \n");
                        printf("P%d\nP%d\n",deadlock_arr[0], j+1 );
                    }
                    else if(deadlock_c > 2)
                    {
                        printf("P%d\n",j+1 );
                    }     
            }
            
            else
            {
                if(nextRate[j]>0)
                {
                    nextRate[j]--;
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

void rms()
{

    system("clear");

    puts("RATE MONOTONIC SCHEDULING ALGORITHM");
    puts("===================================");
    //for()

    getProcesses_rms();

    f=schedulability_rms();

    if(f<=1)
    {
        getPeriodLCM_rms();
        
        schedule_rms();
        printf("\n");
    }
    else{
         printf("\nThis Real time system is not schedulable because %f > 1\n",f);
         FILE *OutputFile;
         OutputFile = fopen("/home/charmi/Desktop/OS PROJECT/output/output_rms.txt","w");
         fprintf(OutputFile,"This Real time system is not schedulable because %f > 1",f);
         fclose(OutputFile);
         //exit(0);
    }
}
