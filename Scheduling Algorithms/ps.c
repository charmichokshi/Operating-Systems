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
} Process;

void print_table(Process p[], int n);
void print_gantt_chart(Process p[], int n);
void ps(Process p[], int n);

int main()
{
	system("clear");
	Process p[MAX];
	int i, j, n;
	int sum_waiting_time = 0, sum_turnaround_time;


	printf("Enter total number of process: ");
	scanf("%d", &n);
	printf("\nEnter Burst Time and Priority for each process:\n");

	for(i=0; i<n; i++) {
		p[i].pid = i+1;
		printf("Burst Time of P[%d] : ", i+1);
		scanf("%d", &p[i].burst_time);

		printf("Priority of P[%d] : ", i+1);
		scanf("%d", &p[i].priority);
	}

	ps(p,n);

	
	return 0;
}

void ps(Process p[], int n)
{
	int pos=0, temp=0, i=0, j=0, total_wt=0, total_tt=0;
	int tt[MAX];

	//sorting burst time, priority and process number in ascending order using selection sort
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

		total_wt = total_wt + p[i].waiting_time;
	}




	for(i=0;i<n;i++)
	{
		p[i].turnaround_time=p[i].burst_time+p[i].waiting_time;     //calculate turnaround time
		total_tt = total_tt + p[i].turnaround_time;

	}



	// print table
	puts(""); // Empty line
	print_table(p, n);
	puts(""); // Empty Line
	printf("Total Waiting Time      : %-2d\n", total_wt);
	printf("Average Waiting Time    : %-2.2lf\n", (double)total_wt / (double) n);
	printf("Total Turnaround Time   : %-2d\n", total_tt);
	printf("Average Turnaround Time : %-2.2lf\n", (double)total_tt / (double) n);

	// print Gantt chart
	puts(""); // Empty line
	//puts("          ***************          ");
	puts("          * GANTT CHART *      ");
	//puts("          ***************          ");
	puts(""); // Empty line
	print_gantt_chart(p, n);
}

void print_table(Process p[], int n)
{
	int i;

	puts("+-----+------------+--------------+-----------------+");
	puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
	puts("+-----+------------+--------------+-----------------+");

	for(i=0; i<n; i++) {
	printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
	       , p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time );
	puts("+-----+------------+--------------+-----------------+");
	}
}

void print_gantt_chart(Process p[], int n)
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
