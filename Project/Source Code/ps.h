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
    int priority;
} Process_ps;

void print_table_ps(Process_ps p[], int n);
void print_gantt_chart_ps(Process_ps p[], int n);
void do_ps(Process_ps p[], int n);

int total_wt_ps=0, total_tt_ps=0;
int th_put_p=0, th_cnt_p=0;

void ps()
{
	system("clear");
	total_wt_ps=0, total_tt_ps=0;
	th_put_p=0, th_cnt_p=0;

	puts("PRIORITY SCHEDULING ALGORITHM");
    puts("==============================");

	Process_ps p[MAX];
	int i, j, n;
	
	printf("\nEnter total number of Process: ");
	scanf("%d", &n);
	printf("\nEnter Burst Time and Priority for each process:\n");

	for(i=0; i<n; i++) 
	{
		p[i].pid = i+1;
		printf("\nBurst Time of P[%d]: ", i+1);
		scanf("%d", &p[i].burst_time);

		printf("Priority of P[%d]  : ", i+1);
		scanf("%d", &p[i].priority);
	}

	printf("\nEnter Throughput time to test for: ");
    scanf("%d", &th_put_p);

	do_ps(p,n);
}

void ps_file_ip()
{
	Process_ps p[MAX];
	total_wt_ps=0, total_tt_ps=0;
	int i, j, n;
	th_put_p=0, th_cnt_p=0;
	char help[255];


	// int sum_waiting_time = 0, sum_turnaround_time;

	FILE *fp1;

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/input/ps_ip.txt", "r");

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

        fgets(help, 255, fp1);
        p[i].priority=atoi(help);
    }

    fgets(help, 255, fp1);
    th_put_p=atoi(help);

	fclose(fp1);
	do_ps(p,n);
	system("clear");
}

void do_ps(Process_ps p[], int n)
{
	int pos=0, temp=0, i=0, j=0;
	int tt[MAX];

	//sorting burst time, priority and Process_ps number in ascending order using selection sort
	for(i=0;i<n;i++)
	{
		pos=i;
		for(j=i+1;j<n;j++)
		{
		    if(p[j].priority < p[pos].priority)
			pos=j;
		}

		temp=p[i].priority;
		p[i].priority=p[pos].priority;
		p[pos].priority=temp;

		temp=p[i].burst_time;
		p[i].burst_time=p[pos].burst_time;
		p[pos].burst_time=temp;

		temp=p[i].pid;
		p[i].pid=p[pos].pid;
		p[pos].pid=temp;
	}

	p[0].waiting_time=0;    //waiting time for first process is zero
 
	//calculate waiting time
	for(i=1;i<n;i++)
	{
		p[i].waiting_time=0;  
		for(j=0;j<i;j++)
		    p[i].waiting_time = p[i].waiting_time + p[j].burst_time;

		total_wt_ps = total_wt_ps + p[i].waiting_time;
	}

	for(i=0;i<n;i++)
	{
		p[i].turnaround_time=p[i].burst_time+p[i].waiting_time;     //calculate turnaround time
		total_tt_ps = total_tt_ps + p[i].turnaround_time;
	}

	for(i=0;i<n;i++)
	{
		if(p[i].turnaround_time <= th_put_p)
			th_cnt_p++;
	}
	// print table
	puts(""); // Empty line

	// print Gantt chart
	puts(""); // Empty line
	puts("          * GANTT CHART *      ");
	puts(""); // Empty line
	print_gantt_chart_ps(p, n);
	
	print_table_ps(p, n);
	puts(""); // Empty Line
	printf("Total Waiting Time      : %-2d\n", total_wt_ps);
	printf("Average Waiting Time    : %-2.2lf\n", (double)total_wt_ps / (double) n);
	printf("Total Turnaround Time   : %-2d\n", total_tt_ps);
	printf("Average Turnaround Time : %-2.2lf\n", (double)total_tt_ps / (double) n);
    printf("Throughput for %d ms is : %d\n", th_put_p,th_cnt_p);	
}

void print_table_ps(Process_ps p[], int n)
{
	int i,j,temp=0;
	int s=p[0].waiting_time;
    int ss=0;	

	FILE* fp = NULL;
	FILE* fp1 = NULL;

	fp=fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_ps.txt","a");
	truncate("/home/charmi/Desktop/OS PROJECT/plot_data/data_ps.txt", 0);

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
	    {
	        printf("An error occoured!");
	    }
	    else
	    {
	        fprintf(fp, "%d\n", p[i].waiting_time);
	    }

	    if(p[i].waiting_time>s) {
            s=p[i].waiting_time;
            ss=i+1;
        }

    }

    fprintf(fp1, "\nAlgorithm: PS      Most Starved Process: P%d      Wait Time (ms): %d", ss,s);       //printing process which starves the most in file

	for(i=0; i<n; i++) 
	{
		if(fp==NULL)
	    {
	        printf("An error occoured!");
	    }
	    else
	    {
	        fprintf(fp, "%d\n", p[i].turnaround_time);
	    }
	}

    fprintf(fp, "%d\n", total_wt_ps / n);
    fprintf(fp, "%d\n", total_tt_ps / n);
    fprintf(fp, "%d",  th_cnt_p);

	fclose(fp);
	fclose(fp1);
}

void print_gantt_chart_ps(Process_ps p[], int n)
{
	int i, j;
	// print top bar
	printf(" ");
	for(i=0; i<n; i++) {
	for(j=0; j<p[i].burst_time; j++) 
		printf("--");
	printf(" ");
	}
	printf("\n|");

	// printing process id in the middle
	for(i=0; i<n; i++) {
	for(j=0; j<p[i].burst_time - 1; j++) 
		printf(" ");
	printf("P%d", p[i].pid);
	for(j=0; j<p[i].burst_time - 1; j++) 
		printf(" ");
	printf("|");
	}
	printf("\n ");

	// printing bottom bar
	for(i=0; i<n; i++) {
	for(j=0; j<p[i].burst_time; j++) printf("--");
	printf(" ");
	}
	printf("\n");

	// printing the time line
	printf("0");
	for(i=0; i<n; i++) {
	for(j=0; j<p[i].burst_time; j++) 
		printf("  ");
	if(p[i].turnaround_time > 9) 
		printf("\b"); // backspace : remove 1 space
	printf("%d", p[i].turnaround_time);
	}
	printf("\n\n");
} 
