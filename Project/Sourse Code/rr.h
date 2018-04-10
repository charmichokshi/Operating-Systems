// C program for implementation of RR scheduling
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX 100

// Function to find the waiting time for all processes
void print_table_rr(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]);

int total_wt = 0, total_tat = 0, cs=0, throughput=0, cnt_th=0;
char help[255];

int findWaitingTime_rr(int processes[], int n, int bt[], int wt[], int quantum)
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
 
    int t = 0; // Current time
    int cs = 0, pre = 0;
    int temp[1] = {101};

    int print[MAX];
    int print_cnt = 0;
 
    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        bool done = true;
 
        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0 && processes[i] != temp[0])
            {
                cs++;
            }

            if (rem_bt[i] > 0)
            {
                print[print_cnt++]=i+1;
            }
            

            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process
 
                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;
 
                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                }
 
                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t = t + rem_bt[i];
 
                    // Waiting time is current time minus time
                    // used by this process
                    wt[i] = t - bt[i];
 
                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }

            temp[0] = processes[i];
            }
        }
 
        // If all processes are done
        if (done == true)
          break;
    }

    printf("\n\n    ***GANTT CHART***\n\n");
    for (int i = 0; i <print_cnt; i++)
    {
        if(i == print_cnt-1)
            printf("| P%d |", print[i]);
        else
            printf("| P%d | -> ", print[i]);
    }
    printf("\n\n");

    return (cs-1);
}
 
// Function to calculate turn around time
void findTurnAroundTime_rr(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    cnt_th=0;
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];

    for (int i = 0; i < n; ++i)
    {
        if (tat[i]<=throughput)
        {
            cnt_th++;
        }
    }
}
 
// Function to calculate average time
void findavgTime_rr(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n];
    total_wt = 0, total_tat = 0, cs = 0;
 
    // Function to find waiting time of all processes
    cs = findWaitingTime_rr(processes, n, bt, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTime_rr(processes, n, bt, wt, tat);
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }

    // print table
    puts(""); // Empty line
    print_table_rr(processes, n, bt, wt, tat);
    puts(""); // Empty Line
    printf("Total Waiting Time              : %-2d\n", total_wt);
    printf("Average Waiting Time            : %-2.2lf\n", (double)total_wt / (double) n);
    printf("Total Turnaround Time           : %-2d\n", total_tat);
    printf("Average Turnaround Time         : %-2.2lf\n", (double)total_tat / (double) n);
    printf("Total number of Context Switches: %d\n", cs);
    printf("Throughput for %d ms is          : %d\n", throughput,cnt_th);
}
 
void cmp_findavgTime_rr(int processes[], int n, int bt[], int quantum, int t)
{
    int wt[n], tat[n];
    total_wt = 0, total_tat = 0, cs = 0;
    throughput=t;
 
    // Function to find waiting time of all processes
    cs = findWaitingTime_rr(processes, n, bt, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTime_rr(processes, n, bt, wt, tat);
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }

    // print table
    puts(""); // Empty line
    print_table_rr(processes, n, bt, wt, tat);
    puts(""); // Empty Line
    printf("Total Waiting Time              : %-2d\n", total_wt);
    printf("Average Waiting Time            : %-2.2lf\n", (double)total_wt / (double) n);
    printf("Total Turnaround Time           : %-2d\n", total_tat);
    printf("Average Turnaround Time         : %-2.2lf\n", (double)total_tat / (double) n);
    printf("Total number of Context Switches: %d\n", cs);
    printf("Throughput for %d ms is         : %d\n", throughput,cnt_th);
}

void print_table_rr(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[])
{
    int i, j, temp, s=waiting_time[0],ss=0;

    FILE* fp = NULL;
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;

    fp=fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_rr.txt","a");
    truncate("/home/charmi/Desktop/OS PROJECT/plot_data/data_rr.txt", 0);

    fp1=fopen("/home/charmi/Desktop/OS PROJECT/plot_data/rr_cmp_data.txt","a");
    truncate("/home/charmi/Desktop/OS PROJECT/plot_data/rr_cmp_data.txt", 0);

    fp2=fopen("/home/charmi/Desktop/OS PROJECT/output/starve_data.txt","a");
    // truncate("/home/charmi/Desktop/OS PROJECT/plot_data/rr_cmp_data.txt", 0);

    puts("+-----+------------+--------------+-----------------+");
    puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
    puts("+-----+------------+--------------+-----------------+");

        /*   Bubble sorting begins */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (n - i - 1); j++)
        {
            if (processes[j] > processes[j + 1])
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;

                temp=burst_time[j];
                burst_time[j]=burst_time[j+1];
                burst_time[j+1]=temp;
         
                temp = waiting_time[j];
                waiting_time[j] = waiting_time[j + 1];
                waiting_time[j + 1] = temp;

                temp = turnaround_time[j];
                turnaround_time[j] = turnaround_time[j + 1];
                turnaround_time[j + 1] = temp;
            }
        }
    }


    for(i=0; i<n; i++) 
    {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
               , processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
        puts("+-----+------------+--------------+-----------------+");

            if(fp==NULL)
                printf("An error occoured!");
            else
                fprintf(fp, "%d\n", waiting_time[i]);

            if(waiting_time[i]>s) 
            {
                s=waiting_time[i];
                ss=i+1;
            }
    }

    fprintf(fp2, "\nAlgorithm: RR      Most Starved Process: P%d      Wait Time (ms): %d", ss,s);       //printing process which starves the most in file

    for(i=0; i<n; i++) 
    {
        if(fp==NULL)
            printf("An error occoured!");
        else
            fprintf(fp, "%d\n", turnaround_time[i]);
    }
 
    fprintf(fp, "%d\n", total_wt / n);
    fprintf(fp, "%d\n", total_tat / n);
    fprintf(fp, "%d",  cnt_th);

    fprintf(fp1, "%d\n", total_wt / n);
    fprintf(fp1, "%d\n", total_tat / n);
    fprintf(fp1, "%d\n", cs);
    fprintf(fp1, "%d", cnt_th);

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
}


void rr_file_ip()
{
    total_wt = 0, total_tat = 0, throughput=0;
    int processes[MAX];
    int burst_time[MAX];
    char help[255];

    int quantum = 0, n = 0;

    FILE *fp1;

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/input/rr_ip.txt", "r");

    if (fp1 == NULL){
        printf("Error Reading File\n");
        exit (0);
    }

    fgets(help, 255, fp1);
    n =atoi(help);

    for(int i=0; i<n; i++)
    {
        processes[i] = i+1;

        fgets(help, 255, fp1);
        burst_time[i]=atoi(help);
    }

    fgets(help, 255, fp1);
    quantum=atoi(help);

    fgets(help, 255, fp1);
    throughput=atoi(help);

    fclose(fp1);

    findavgTime_rr(processes, n, burst_time, quantum);
    system("clear");
}

void rr()
{
    system("clear");

    total_wt = 0, total_tat = 0, cs=0, throughput=0;

    puts("ROUND ROBIN SCHEDULING ALGORITHM");
    puts("================================");

    // process id's
    int processes[MAX];
    int burst_time[MAX];
    int quantum = 0, n = 0;

    printf("\nEnter total number of process: ");
    scanf("%d", &n);

    printf("\nEnter Burst Time for each process:\n");

    for(int i=0; i<n; i++) {
        processes[i] = i+1;
        printf("Burst Time of P[%d] : ", i+1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter time Quantum: ");
    scanf("%d", &quantum);

    printf("Enter Throughput time to test for: ");
    scanf("%d", &throughput);

    findavgTime_rr(processes, n, burst_time, quantum);
}