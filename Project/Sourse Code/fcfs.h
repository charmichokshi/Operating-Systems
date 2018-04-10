//Program - Header file for implementation of first come first serve 
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//Arrival time of each process is assumed 0 in this program.

typedef struct
{
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void print_table_fcfs(Process p[], int n);
void print_gantt_chart_fcfs(Process p[], int n);

int sum_waiting_time = 0, sum_turnaround_time=0;
int th_put=0,th_cn=0;

void fcfs()
{
	system("clear");

	th_put=0,th_cn=0;

	puts("FIRST COME FIRST SERVE SCHEDULING ALGORITHM");
    puts("===========================================");

	Process p[MAX];
	int i, j, n;
	sum_waiting_time = 0, sum_turnaround_time=0;

	printf("\nEnter total number of process: ");
	scanf("%d", &n);
	printf("\nEnter burst time for each process:\n");
	for(i=0; i<n; i++) 
	{
		p[i].pid = i+1;
		printf("P[%d] : ", i+1);
		scanf("%d", &p[i].burst_time);
		p[i].waiting_time = p[i].turnaround_time = 0;
	}

	printf("Enter Throughput time to test for: ");
    scanf("%d", &th_put);

	// calculate waiting time and turnaround time
	p[0].turnaround_time = p[0].burst_time;

	for(i=1; i<n; i++) 
	{
		p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
		p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
	}

	// calculate sum of waiting time and sum of turnaround time
	for(i=0; i<n; i++) 
	{
	    sum_waiting_time += p[i].waiting_time;
	    sum_turnaround_time += p[i].turnaround_time;
	}

	for (int i = 0; i < n; ++i)
    {
        if (p[i].turnaround_time <= th_put)
            th_cn++;
    }

	// print table
	puts(""); // Empty line
	print_table_fcfs(p, n);
	puts(""); // Empty Line
	printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
	printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
	printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
	printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);
	printf("Throughput for %d ms is  : %d\n", th_put,th_cn);

	// print Gantt chart
	puts(""); // Empty line
	//puts("          ***************          ");
	puts("          * GANTT CHART *      ");
	//puts("          ***************          ");
	puts(""); // Empty line
	print_gantt_chart_fcfs(p, n);
}

void fcfs_file_ip()
{
	sum_waiting_time = 0, sum_turnaround_time=0,th_cn=0,th_put=0;

	Process p[MAX];
	int burst_time[MAX];
	char help[255]; 
    int n = 0;
	int i, j;

    FILE *fp1;

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/input/fcfs_ip.txt", "r");

    if (fp1 == NULL){
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

        p[i].waiting_time = p[i].turnaround_time = 0;
    }

    fgets(help, 255, fp1);
    th_put=atoi(help);

	fclose(fp1);

	// calculate waiting time and turnaround time
	p[0].turnaround_time = p[0].burst_time;

	for(i=1; i<n; i++) {
		p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
		p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
	}

	// calculate sum of waiting time and sum of turnaround time
	for(i=0; i<n; i++) {
	    sum_waiting_time += p[i].waiting_time;
	    sum_turnaround_time += p[i].turnaround_time;
	}

	for (int i = 0; i < n; ++i)
    {
        if (p[i].turnaround_time <= th_put)
            th_cn++;
    }


	// print table
	puts(""); // Empty line
	print_table_fcfs(p, n);
	puts(""); // Empty Line
	printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
	printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
	printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
	printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);
	printf("Throughput for %d ms is  : %d\n", th_put,th_cn);

	// print Gantt chart
	puts(""); // Empty line
	puts("          * GANTT CHART *      ");
	puts(""); // Empty line
	print_gantt_chart_fcfs(p, n);

	system("clear");
}


void print_table_fcfs(Process p[], int n)
{
	int i;
	int s=p[0].waiting_time;
    int ss=0;

	FILE* fp = NULL;
	FILE* fp1 = NULL;

	fp=fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_fcfs.txt","a");
	truncate("/home/charmi/Desktop/OS PROJECT/plot_data/data_fcfs.txt", 0);

	fp1=fopen("/home/charmi/Desktop/OS PROJECT/output/starve_data.txt","a");
	truncate("/home/charmi/Desktop/OS PROJECT/output/starve_data.txt", 0);

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
	
	    if(p[i].waiting_time>s) {
            s=p[i].waiting_time;
            ss=i+1;
        }
    }

    fprintf(fp1, "\nAlgorithm: FCFS    Most Starved Process: P%d      Wait Time (ms): %d", ss,s);       //printing process which starves the most in file

	for(i=0; i<n; i++) 
	{
		if(fp==NULL)
	        printf("An error occoured!");
	    else
	        fprintf(fp, "%d\n", p[i].turnaround_time);
	}
 
    fprintf(fp, "%d\n", sum_waiting_time / n);
    fprintf(fp, "%d\n", sum_turnaround_time / n);
    fprintf(fp, "%d",  th_cn);

	fclose(fp);
	fclose(fp1);
}

void print_gantt_chart_fcfs(Process p[], int n)
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