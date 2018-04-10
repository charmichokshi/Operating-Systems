// C program for implementation of RR scheduling

/*
code o/p: 7
real o/p: 8

*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 100
 
// Function to find the waiting time for all
// processes
void print_table(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]);

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

    int cs=0;

    int pre = n-1;

    int print[MAX];
    int print_cnt = 0;

    // int 
 
    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        // bool done = true;
 
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
            cs=n-1;
         quantum = quantum*2;
        }

        
        

        else
        {

            int i=0, pos=0, temp=0;
            int cnt_break=0;
            // pre = n-1;
            //sorting burst time in ascending order using selection sort
        // printf("\n%d %d\n",pre,j);
        // printf("**ji %d\n",processes[0]);

            // pos=i;
            for(int j=i+1;j<n;j++)
            {
                if (rem_bt[pos] == 0)
                {
                    /* code */
                    pos++;
                }

                if (rem_bt[j] != 0)
                {
                    /* code */

                    if(rem_bt[j] < rem_bt[pos])
                    {
                        pos=j;
                        // cs++;
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
                /* code */
                break;
            }
              

                // else
// printf("\nhi %d\n",cs);
                
            if ((cnt == 2) && (processes[pos] != processes[n-1]))
            {
                cs++;
                cnt++;
            }
            else if (processes[pos] != processes[0])
            {
                cs++;
            }

// printf("\n***%d\n",pos+1 );


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


// for (int i = 0; i < n; ++i)
// {
//      code 
//     printf("\n%d",processes[i]);
// }

            // If burst time of a process is greater than 0
            // then only need to process further

            i=0;
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
    return cs;
}
 
// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
 
// Function to calculate average time

void findavgTime(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
 
    // Function to find waiting time of all processes
    int cs = findWaitingTime(processes, n, bt, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }

    // print table
    puts(""); // Empty line
    print_table(processes, n, bt, wt, tat);
    puts(""); // Empty Line
    printf("Total Waiting Time              : %-2d\n", total_wt);
    printf("Average Waiting Time            : %-2.2lf\n", (double)total_wt / (double) n);
    printf("Total Turnaround Time           : %-2d\n", total_tat);
    printf("Average Turnaround Time         : %-2.2lf\n", (double)total_tat / (double) n);
    printf("Total number of Context Switches: %d\n\n", cs);
}
 
void print_table(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[])
{
    int i=0, temp = 0, j=0;

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
}

// Driver code
int main()
{
    // process id's
    int processes[MAX];
 
    // Burst time of all processes
    int burst_time[MAX];
 
    // Time quantum
    int quantum = 0, n = 0;

    printf("Enter total number of process: ");
    scanf("%d", &n);

    printf("\nEnter Burst Time for each process:\n");

    for(int i=0; i<n; i++) {
        processes[i] = i+1;
        printf("Burst Time of P[%d] : ", i+1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter time Quantum: ");
    scanf("%d", &quantum);


    findavgTime(processes, n, burst_time, quantum);
    return 0;
}