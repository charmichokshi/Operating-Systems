#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 100

struct process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

typedef struct process Process;


double average_waiting_time;
double average_turnaround_time;
int total_waiting_time;
int total_turnaround_time;

void sort_process_by_burst_time(Process p[], int n);
void calculate_waiting_time(Process p[], int n);
void print_gantt_chart(Process p[], int n);
void print_table(Process p[], int n);
void calculate_trurn_around_time(Process p[], int n);

int main()
{
    Process p[MAX_PROCESS];
    int n, i, j;
    puts("SHORTEST JOB FIRST SCHEDULING ALGORITHM");
    puts("=======================================");

    printf("Enter total process: ");
    scanf("%d", &n);
    printf("\nEnter burst time for each process:\n");
    for(i=0; i<n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i+1;
    }



    sort_process_by_burst_time(p, n);
    calculate_waiting_time(p, n);
    calculate_trurn_around_time(p, n);

    average_waiting_time = (double) ( (double)total_waiting_time / (double) n );
    average_turnaround_time = (double) ( (double)total_turnaround_time / (double) n );

    print_table(p, n);
    puts("");
    printf("Total Waiting Time      : %-2d\n", total_waiting_time);
    printf("Average Waiting Time    : %.2lf\n",average_waiting_time);
    printf("Total Turnaround Time   : %-2d\n", total_turnaround_time);
    printf("Average Turnaround Time : %.2lf\n",average_turnaround_time);

    printf("\n* Gantt Chart *\n");
    print_gantt_chart(p, n);


    return 0;
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

void sort_process_by_burst_time(Process p[], int n)
{
    int i, j;
    Process temp;
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-1-i; j++) {
            if(p[j].burst_time > p[j+1].burst_time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void calculate_waiting_time(Process p[], int n)
{
    int i;
    total_waiting_time = 0;
    p[0].waiting_time = 0;
    for(i=1; i<n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
        total_waiting_time += p[i].waiting_time;
    }
}

void calculate_trurn_around_time(Process p[], int n)
{
    int i;
    total_turnaround_time = 0;
    //p[0].waiting_time = 0;
    for(i=0; i<n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        total_turnaround_time += p[i].turnaround_time;
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
