//Program - This header file contains implementation of modified round robin algorithm
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
 
void print_table(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]);

    int cs_mrr=0;
    int total_wt_mrr = 0, total_tat_mrr = 0, th=0, c_th=0;

int findWaitingTime(int processes[], int n,
             int bt[], int wt[], int quantum)
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
 
    int t = 0; // Current time

    int cnt = 1;
    int pre = n-1;

    int print[MAX];
    int print_cnt = 0;
    
    while (1)
    { 
        if(cnt == 1)
        {
            // Traverse all processes one by one repeatedly
            for (int i = 0 ; i < n; i++)
            {
                print[print_cnt++]=i+1;
                // If burst time of a process is greater than 0
                // then only need to process further
                if (rem_bt[i] > 0)
                {
                    // done = false; // There is a pending process
     
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
                }
            }

            cnt++;
            cs_mrr=n-1;
            quantum = quantum*2;
        }

        else
        {

            int i=0, pos=0, temp=0;
            int cnt_break=0;
            
            for(int j=i+1;j<n;j++)
            {
                if (rem_bt[pos] == 0)
                {
                    pos++;
                }

                if (rem_bt[j] != 0)
                {
                    if(rem_bt[j] < rem_bt[pos])
                    {
                        pos=j;
                    }
                }
            }

            for (int i = 0; i < n; i++)
            {
                if (rem_bt[i]==0)
                {
                    cnt_break++;
                }
            }
            if (cnt_break == n)
            {
                break;
            }
              
            if ((cnt == 2) && (processes[pos] != processes[n-1]))
            {
                cs_mrr++;
                cnt++;
            }
            else if (processes[pos] != processes[0])
            {
                cs_mrr++;
            }

            //sorting the list
            i=0;

            temp=bt[i];
            bt[i]=bt[pos];
            bt[pos]=temp;
     
            temp=processes[i];
            processes[i]=processes[pos];
            processes[pos]=temp;

            temp=rem_bt[i];
            rem_bt[i]=rem_bt[pos];
            rem_bt[pos]=temp;
     
            temp=wt[i];
            wt[i]=wt[pos];
            wt[pos]=temp;

            print[print_cnt++]=processes[i];

            i=0;
            if (rem_bt[i] > 0)
            { 
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
            }
            else
                break;
        }
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
    return cs_mrr;
}
 
// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    c_th=0;

    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];

    for (int i = 0; i < n; ++i)
    {
        if (tat[i]<=th)
        {
            c_th++;
        }
    }
}
 
// Function to calculate average time

void findavgTime(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n];

    cs_mrr=0, total_wt_mrr = 0, total_tat_mrr = 0;
 
    // Function to find waiting time of all processes
    cs_mrr = findWaitingTime(processes, n, bt, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt_mrr = total_wt_mrr + wt[i];
        total_tat_mrr = total_tat_mrr + tat[i];
    }

    // print table
    puts(""); // Empty line
    print_table(processes, n, bt, wt, tat);
    puts(""); // Empty Line
    printf("Total Waiting Time              : %-2d\n", total_wt_mrr);
    printf("Average Waiting Time            : %-2.2lf\n", (double)total_wt_mrr / (double) n);
    printf("Total Turnaround Time           : %-2d\n", total_tat_mrr);
    printf("Average Turnaround Time         : %-2.2lf\n", (double)total_tat_mrr / (double) n);
    printf("Total number of Context Switches: %d\n", cs_mrr);
    printf("Throughput for %d ms is          : %d\n\n", th,c_th);

}

void cmp_findavgTime(int processes[], int n, int bt[], int quantum, int t)
{
    int wt[n], tat[n];
    th=t;
    cs_mrr=0, total_wt_mrr = 0, total_tat_mrr = 0;
 
    // Function to find waiting time of all processes
    cs_mrr = findWaitingTime(processes, n, bt, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt_mrr = total_wt_mrr + wt[i];
        total_tat_mrr = total_tat_mrr + tat[i];
    }

    // print table
    puts(""); // Empty line
    print_table(processes, n, bt, wt, tat);
    puts(""); // Empty Line
    printf("Total Waiting Time              : %-2d\n", total_wt_mrr);
    printf("Average Waiting Time            : %-2.2lf\n", (double)total_wt_mrr / (double) n);
    printf("Total Turnaround Time           : %-2d\n", total_tat_mrr);
    printf("Average Turnaround Time         : %-2.2lf\n", (double)total_tat_mrr / (double) n);
    printf("Total number of Context Switches: %d\n", cs_mrr);
    printf("Throughput for %d ms is          : %d\n\n", th,c_th);

}
 
void print_table(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[])
{
    int i=0, temp = 0, j=0;

    FILE* fp1 = NULL;

    fp1=fopen("/home/charmi/Desktop/OS PROJECT/plot_data/mrr_cmp_data.txt","a");
    truncate("/home/charmi/Desktop/OS PROJECT/plot_data/mrr_cmp_data.txt", 0);

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


    for(i=0; i<n; i++) {
    printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
           , processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    puts("+-----+------------+--------------+-----------------+");
    }

    fprintf(fp1, "%d\n", total_wt_mrr / n);
    fprintf(fp1, "%d\n", total_tat_mrr / n);
    fprintf(fp1, "%d\n", cs_mrr);
    fprintf(fp1, "%d", c_th);

    fclose(fp1);
}

// Driver code
void modified_rr()
{
    system("clear");
    cs_mrr=0, total_wt_mrr = 0, total_tat_mrr = 0, th=0;

    puts("MODIFIED ROUND ROBIN SCHEDULING ALGORITHM");
    puts("=========================================");

    // process id's
    int processes[MAX];
 
    // Burst time of all processes
    int burst_time[MAX];
 
    // Time quantum
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
    scanf("%d", &th);

    findavgTime(processes, n, burst_time, quantum);
}