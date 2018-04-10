//Program - This header file contains comparison of Round robin and modified Round robin
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

char temp[255];

void rr_cmp()
{
    int processes[MAX];
    int burst_time[MAX];
 
    int quantum = 0, n = 0, throughput=0;

    FILE *fp1;

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/input/rr_mrr_cmp_ip.txt", "r");

    if (fp1 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }

    fgets(temp, 255, fp1);
    n =atoi(temp);

    for(int i=0; i<n; i++)
    {
        processes[i] = i+1;
        fgets(temp, 255, fp1);
        burst_time[i]=atoi(temp);
    }

    fgets(temp, 255, fp1);
    quantum=atoi(temp);

    fgets(temp, 255, fp1);
    throughput=atoi(temp);

    fclose(fp1);

    cmp_findavgTime_rr(processes, n, burst_time, quantum, throughput);

    mrr_cmp();
}

void mrr_cmp()
{
    int processes[MAX];
    int burst_time[MAX];
 
    int quantum = 0, n = 0, t=0;

    FILE *fp1;
    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/input/rr_mrr_cmp_ip.txt", "r");

    if (fp1 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }

    fgets(temp, 255, fp1);
    n =atoi(temp);

    for(int i=0; i<n; i++)
    {
        processes[i] = i+1;
        fgets(temp, 255, fp1);
        burst_time[i]=atoi(temp);
    }

    fgets(temp, 255, fp1);
    quantum=atoi(temp);

    fgets(temp, 255, fp1);
    t=atoi(temp);

    fclose(fp1);

    cmp_findavgTime(processes, n, burst_time, quantum, t);
    system("clear");
}