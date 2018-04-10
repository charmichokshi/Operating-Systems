/*

College : School of Engineering and Applied Science
Course  : Information and Communication Technology
Semester: 5th
Subject : Operating Systems Lab
Faculty : Dr. Sanjay Choudhary, Prof. M. T. Savaliya
Project : CPU Scheduling Algorithm
Group No: 02

Group Members:
Charmi Chokshi    (201501021)
Hena Ghonia       (201501032)

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#include "rr.h" // Round robin scheduling algorithm
#include "fcfs.h"//First come first serve algorithm
#include "sjf.h"//Shortest path first algorithm
#include "ps.h"//Priority scheduling 
#include "modified_rr.h"//Modified Round robin algorithm
#include "plot_cmp_algos.h"//plotting rr, fcfs, sjf and ps
#include "thread.h"
#include "rr_mrr_cmp.h"//Comparison for Round robin and modified Round robin
#include "plot_rr_mrr.h"//plotting rr and modified rr
#include "edf.h"// Earliest deadline first scheduling
#include "rms.h"//Rate monotonic scheduling

void main()
{
	system("clear");
	printf("\n\t***WELCOME TO THE CPU SCHEDULING ALGORITHM SIMULATOR***\n");
    print_menu();
}

 void print_menu()
 {
    int choice = 0;
    do
    {
        printf("\n\t      ~~~MENU~~~\n");
        printf("\n     1. First Come First Serve (FCFS)");
        printf("\n     2. Shortest Job First (SJF)");
        printf("\n     3. Priority Scheduling (PS)");
        printf("\n     4. Round Robin (RR)");
        printf("\n     5. Compare All 4 Algorithms");
        printf("\n     6. Modified Round Robin");
        printf("\n     7. Compare RR and Modified RR");
        printf("\n     8. Earliest Deadline First (EDF)");
        printf("\n     9. Rate Monotonic Scheduling (RMS)");
        printf("\n    10. Exit");

        printf("\n\nWhich Algorithm/ Option you want to Choose? ");
        scanf("%d", &choice);   //choice is stored in choice variable

        switch(choice)
        {
            case 1:
            	fcfs();
            break;

            case 2:
            	sjf();
            break;

            case 3:
            	ps();
            break;

            case 4:
            	rr();
            break;

            case 5:
            	fn_thread();

                plot();

                printf("\nGraphs to Compare all the Algorithms are Generated...\n");
            break;

            case 6:
               modified_rr();
            break;

            case 7:
                rr_cmp();

                plot_rr_mrr();

                printf("\nGraph to Compare RR and Modified RR is Generated...\n");
            break;

            case 8:
               edf();
            break;

            case 9:
               rms();
            break;

            case 10:
            break;

            default:
                printf("\nINVALID CHOICE!!\n");
            break;
		}
    }while(choice != 10);

    printf("\n\t***THANK YOU FOR USING CPU SCHEDULING ALGORITHM SIMULATOR***\n\n\n");
}
