//Program - This header file contains implementation of shortest job first
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 100

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process_sjf;

double average_waiting_time;
double average_turnaround_time;
int total_waiting_time=0, total_turnaround_time=0,th_put_s=0,th_cn_s=0;;

void sort_process_by_burst_time(Process_sjf p[], int n);
void calculate_waiting_time(Process_sjf p[], int n);
void print_gantt_chart_sjf(Process_sjf p[], int n);
void print_table_sjf(Process_sjf p[], int n);
void calculate_trurn_around_time(Process_sjf p[], int n);

void sjf()
{
    system("clear");
    total_waiting_time=0, total_turnaround_time=0;

    Process_sjf p[MAX_PROCESS];
    int n, i, j;
    puts("SHORTEST JOB FIRST SCHEDULING ALGORITHM");
    puts("=======================================");
    printf("\nEnter total process: ");
    scanf("%d", &n);
    printf("\nEnter burst time for each process:\n");
    
    for(i=0; i<n; i++) 
    {
        printf("P[%d]: ", i+1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i+1;
    }
    printf("\n");

    printf("Enter Throughput time to test for: ");
    scanf("%d", &th_put_s);

    sort_process_by_burst_time(p, n);
    calculate_waiting_time(p, n);
    calculate_trurn_around_time(p, n);

    average_waiting_time = (double) ( (double)total_waiting_time / (double) n );
    average_turnaround_time = (double) ( (double)total_turnaround_time / (double) n );

    printf("\n* Gantt Chart *\n");
    print_gantt_chart_sjf(p, n);

    print_table_sjf(p, n);
    puts("");
    printf("Total Waiting Time      : %-2d\n", total_waiting_time);
    printf("Average Waiting Time    : %.2lf\n",average_waiting_time);
    printf("Total Turnaround Time   : %-2d\n", total_turnaround_time);
    printf("Average Turnaround Time : %.2lf\n",average_turnaround_time);
    printf("Throughput for %d ms is : %d\n", th_put_s,th_cn_s);

}

void sjf_file_ip()
{
    th_put_s=0,th_cn_s=0;
    total_waiting_time=0, total_turnaround_time=0;
    Process_sjf p[MAX_PROCESS];
    int n, i, j;
    char help[255];

    FILE *fp1;

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/input/fcfs_ip.txt", "r");

    if (fp1 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }

    fgets(help, 255, fp1);
    n =atoi(help);

    for(int i=0; i<n; i++)
    {
        p[i].pid = i+1;

        fgets(help, 255, fp1);
        p[i].burst_time=atoi(help);
    }

    fgets(help, 255, fp1);
    th_put_s=atoi(help);

    sort_process_by_burst_time(p, n);
    calculate_waiting_time(p, n);
    calculate_trurn_around_time(p, n);

    average_waiting_time = (double) ( (double)total_waiting_time / (double) n );
    average_turnaround_time = (double) ( (double)total_turnaround_time / (double) n );

    printf("\n* Gantt Chart *\n");
    print_gantt_chart_sjf(p, n);

    print_table_sjf(p, n);
    puts("");
    printf("Total Waiting Time      : %-2d\n", total_waiting_time);
    printf("Average Waiting Time    : %.2lf\n",average_waiting_time);
    printf("Total Turnaround Time   : %-2d\n", total_turnaround_time);
    printf("Average Turnaround Time : %.2lf\n",average_turnaround_time);
    printf("Throughput for %d ms is  : %d\n", th_put_s,th_cn_s);


    system("clear");   
    fclose(fp1);
}

void print_table_sjf(Process_sjf p[], int n)
{
	int i,j,temp;

    FILE* fp = NULL;
    FILE* fp1=NULL;

    int s=p[0].waiting_time;
    int ss=0;

    fp=fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_sjf.txt","a");
    truncate("/home/charmi/Desktop/OS PROJECT/plot_data/data_sjf.txt", 0);
    fp1=fopen("/home/charmi/Desktop/OS PROJECT/output/starve_data.txt","a");

    /*   Bubble sorting begins */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (n - i - 1); j++)
        {
            if (p[j].pid > p[j+1].pid)
            {
                temp=p[j].turnaround_time;
                p[j].turnaround_time=p[j+1].turnaround_time;
                p[j+1].turnaround_time=temp;

                temp=p[j].waiting_time;
                p[j].waiting_time=p[j+1].waiting_time;
                p[j+1].waiting_time=temp;

                temp=p[j].burst_time;
                p[j].burst_time=p[j+1].burst_time;
                p[j+1].burst_time=temp;

                temp=p[j].pid;
                p[j].pid=p[j+1].pid;
                p[j+1].pid=temp;
            }
        }
    }

	puts("+-----+------------+--------------+-----------------+");
	puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
	puts("+-----+------------+--------------+-----------------+");

	for(i=0; i<n; i++) 
    {
    	printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
    	       , p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time );
    	puts("+-----+------------+--------------+-----------------+");

        if(fp==NULL)
            printf("An error occoured!");
        else
            fprintf(fp, "%d\n", p[i].waiting_time);

        if(p[i].waiting_time>s) 
        {
            s=p[i].waiting_time;
            ss=i+1;
        }

    }

    fprintf(fp1, "\nAlgorithm: SJF     Most Starved Process: P%d      Wait Time (ms): %d", ss,s);       //printing process which starves the most in file


    for(i=0; i<n; i++) 
    {
        if(fp==NULL)
            printf("An error occoured!");
        else
            fprintf(fp, "%d\n", p[i].turnaround_time);
    }
 
    fprintf(fp, "%d\n", total_waiting_time / n);
    fprintf(fp, "%d\n", total_turnaround_time / n);
    fprintf(fp, "%d",  th_cn_s);

    fclose(fp);
    fclose(fp1);
}

void sort_process_by_burst_time(Process_sjf p[], int n)
{
    int i, j;
    Process_sjf temp;
    for(i=0; i<n-1; i++) 
    {
        for(j=0; j<n-1-i; j++) 
        {
            if(p[j].burst_time > p[j+1].burst_time) 
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void calculate_waiting_time(Process_sjf p[], int n)
{
    int i;
    total_waiting_time = 0;
    p[0].waiting_time = 0;
    for(i=1; i<n; i++) 
    {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
        total_waiting_time += p[i].waiting_time;
    }
}

void calculate_trurn_around_time(Process_sjf p[], int n)
{
    int i;
    total_turnaround_time = 0;
    th_cn_s=0;

    for(i=0; i<n; i++) 
    {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    for(i=0; i<n; i++) 
    {
        if(p[i].turnaround_time <= th_put_s)
            th_cn_s++;
    }
}

void print_gantt_chart_sjf(Process_sjf p[], int n)
{
	int i, j;
	// print top bar
	printf(" ");
	for(i=0; i<n; i++) 
    {
	for(j=0; j<p[i].burst_time; j++) 
		printf("--");
	printf(" ");
	}
	printf("\n|");

	// printing process id in the middle
	for(i=0; i<n; i++) 
    {
	for(j=0; j<p[i].burst_time - 1; j++) 
		printf(" ");
	printf("P%d", p[i].pid);
	for(j=0; j<p[i].burst_time - 1; j++) 
		printf(" ");
	printf("|");
	}
	printf("\n ");

	// printing bottom bar
	for(i=0; i<n; i++) 
    {
	for(j=0; j<p[i].burst_time; j++) printf("--");
	printf(" ");
	}
	printf("\n");

	// printing the time line
	printf("0");
	for(i=0; i<n; i++) 
    {
	for(j=0; j<p[i].burst_time; j++) 
		printf("  ");
	if(p[i].turnaround_time > 9) 
		printf("\b"); // backspace : remove 1 space
	printf("%d", p[i].turnaround_time);
	}
	printf("\n\n");
}
