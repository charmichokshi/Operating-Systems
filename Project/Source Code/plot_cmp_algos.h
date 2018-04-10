//Program - This header file comparison of First come first serve, Round Robin, Priority Scheduling, Shortest Job First and thier code to plot
#include <stdio.h>
#include <stdlib.h>
#include "xlsxwriter.h"

void write_worksheet_data_wt(lxw_worksheet *worksheet, lxw_format *bold) 
{
    int row, col=10, i;

    FILE *fp1, *fp2, *fp3, *fp4;

    int lineNumber, count=0;
    char line[501];

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_fcfs.txt", "r");
    fp2 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_rr.txt", "r");
    fp3 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_ps.txt", "r");
    fp4 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_sjf.txt", "r");

    if (fp1 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }
    if (fp2 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }
    if (fp3 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }
    if (fp4 == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }

    uint8_t data1[5];
    uint8_t data2[5];
    uint8_t data3[5];
    uint8_t data4[5];

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);
    fseek(fp3, 0, SEEK_SET);
    fseek(fp4, 0, SEEK_SET);

    for (i = 0; i < 4; i++)
    {
        fscanf(fp1, "%d\n", &data1[i]);
        fscanf(fp2, "%d\n", &data2[i]);
        fscanf(fp3, "%d\n", &data3[i]);
        fscanf(fp4, "%d\n", &data4[i]);
    }

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);
    fseek(fp3, 0, SEEK_SET);
    fseek(fp4, 0, SEEK_SET);

    lineNumber=7;
    count=0;
    while ((fgets(line, 500, fp1) != NULL) && (fgets(line, 255, fp2) != NULL) && (fgets(line, 255, fp3) != NULL) && (fgets(line, 255, fp4) != NULL)) /* read a line */
    {
        if (count == lineNumber)
        {
            fscanf(fp1, "%d ", &data1[4]);
            fscanf(fp2, "%d ", &data2[4]);
            fscanf(fp3, "%d ", &data3[4]);
            fscanf(fp4, "%d ", &data4[4]);

            break;
        }
        else
            count++;
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    worksheet_write_string(worksheet, CELL("I1"), "Process", bold);
    worksheet_write_string(worksheet, CELL("I2"), "P1", bold);
    worksheet_write_string(worksheet, CELL("I3"), "P2", bold);
    worksheet_write_string(worksheet, CELL("I4"), "P3", bold);
    worksheet_write_string(worksheet, CELL("I5"), "P4", bold);
    worksheet_write_string(worksheet, CELL("I6"), "AvgWT", bold);

    worksheet_write_string(worksheet, CELL("J1"), "FCFS", NULL);
    worksheet_write_string(worksheet, CELL("K1"), "RR", NULL);
    worksheet_write_string(worksheet, CELL("L1"), "PS", NULL);
    worksheet_write_string(worksheet, CELL("M1"), "SJF", NULL);

    for (row = 0; row < 5; row++) 
    {
        worksheet_write_number(worksheet, row+1, 9, data1[row] , NULL);
        worksheet_write_number(worksheet, row+1, 10, data2[row] , NULL);
        worksheet_write_number(worksheet, row+1, 11, data3[row] , NULL);
        worksheet_write_number(worksheet, row+1, 12, data4[row] , NULL);
    }
}

void write_worksheet_data_tt(lxw_worksheet *worksheet, lxw_format *bold) {

    int row, col=1, i;
    int lineNumber, count=0;
    char line[501]; /* or other suitable maximum line size */

	FILE *fp1, *fp2, *fp3, *fp4, *fp;


    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_fcfs.txt", "r");
    fp2 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_rr.txt", "r");
    fp3 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_ps.txt", "r");
    fp4 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/data_sjf.txt", "r");

    if (fp1 == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    if (fp2 == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    if (fp3 == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    if (fp4 == NULL){
        printf("Error Reading File\n");
        exit (0);
    }

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);
    fseek(fp3, 0, SEEK_SET);
    fseek(fp4, 0, SEEK_SET);

    uint8_t data1[6];
    uint8_t data2[6];
    uint8_t data3[6];
    uint8_t data4[6];

    lineNumber=3;
    count=0;
    while ((fgets(line, 500, fp1) != NULL) && (fgets(line, 255, fp2) != NULL) && (fgets(line, 255, fp3) != NULL) && (fgets(line, 255, fp4) != NULL)) /* read a line */
    {
        if (count == lineNumber)
        {
            for (i = 0; i < 4; i++){
                fscanf(fp1, "%d ", &data1[i]);
                fscanf(fp2, "%d ", &data2[i]);
                fscanf(fp3, "%d ", &data3[i]);
                fscanf(fp4, "%d ", &data4[i]);
            }
            break;
        }
        else
        {
            count++;
        }
    }

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);
    fseek(fp3, 0, SEEK_SET);
    fseek(fp4, 0, SEEK_SET);

    lineNumber=8;
    count=0;
    while ((fgets(line, 255, fp1) != NULL) && (fgets(line, 255, fp2) != NULL) && (fgets(line, 255, fp3) != NULL) && (fgets(line, 255, fp4) != NULL)) /* read a line */
    {
        if (count == lineNumber)
        {
            fscanf(fp1, "%d ", &data1[4]);
            fscanf(fp2, "%d ", &data2[4]);
            fscanf(fp3, "%d ", &data3[4]);
            fscanf(fp4, "%d ", &data4[4]);

            fscanf(fp1, "%d ", &data1[5]);
            fscanf(fp2, "%d ", &data2[5]);
            fscanf(fp3, "%d ", &data3[5]);
            fscanf(fp4, "%d ", &data4[5]);
            break;
        }
        else
        {
            count++;
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    worksheet_write_string(worksheet, CELL("A1"), "Process", bold);
    worksheet_write_string(worksheet, CELL("A2"), "P1", bold);
    worksheet_write_string(worksheet, CELL("A3"), "P2", bold);
    worksheet_write_string(worksheet, CELL("A4"), "P3", bold);
    worksheet_write_string(worksheet, CELL("A5"), "P4", bold);
    worksheet_write_string(worksheet, CELL("A6"), "AvgTT", bold);
    worksheet_write_string(worksheet, CELL("A7"), "Throughput", bold);

    worksheet_write_string(worksheet, CELL("B1"), "FCFS", NULL);
    worksheet_write_string(worksheet, CELL("C1"), "RR", NULL);
    worksheet_write_string(worksheet, CELL("D1"), "PS", NULL);
    worksheet_write_string(worksheet, CELL("E1"), "SJF", NULL);


    for (row = 0; row < 6; row++) 
    {
        worksheet_write_number(worksheet, row+1, 1, data1[row] , NULL);
        worksheet_write_number(worksheet, row+1, 2, data2[row] , NULL);
        worksheet_write_number(worksheet, row+1, 3, data3[row] , NULL);
        worksheet_write_number(worksheet, row+1, 4, data4[row] , NULL);
    }
}

/*
 * Create a worksheet with examples charts.
 */
int plot() {

    lxw_workbook     *workbook  = new_workbook("/home/charmi/Desktop/OS PROJECT/plot/plot_cmp_algos.xlsx");
    lxw_worksheet    *worksheet = workbook_add_worksheet(workbook, NULL);
    lxw_chart_series *series;

    /* Add a bold format to use to highlight the header cells. */
    lxw_format *bold = workbook_add_format(workbook);
    format_set_bold(bold);

    /* Write some data for the chart. */
    write_worksheet_data_tt(worksheet, bold);


//PLOTING TT AND ATT

    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);

    /* Add the first series to the chart. */
    series = chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$B$2:$B$7");
    /* Set the name for the series instead of the default "Series 1". */
    chart_series_set_name(series, "FCFS");


    series = chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$C$2:$C$7");
	chart_series_set_name(series, "RR");

    series = chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!D$2:$D$7");
    chart_series_set_name(series, "PS");

    series = chart_add_series(chart, "=Sheet1!$A$2:$A$7", "=Sheet1!$E$2:$E$7");
    chart_series_set_name(series, "SJF");

    /* Add a chart title and some axis labels. */
    chart_title_set_name(chart, "Turnaround time and Avg. Turnaround Time");
    chart_axis_set_name(chart->y_axis, "Time (ms)");
    chart_axis_set_name(chart->x_axis, "Process ID");

    /* Set an Excel chart style. */
    //chart_set_style(chart, 7);

    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet, CELL("A9"), chart);

//PLOTING WT AWT
    lxw_chart *chart2 = workbook_add_chart(workbook, LXW_CHART_COLUMN);
    lxw_chart_series *series2;

    write_worksheet_data_wt(worksheet, bold);
    // lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);

    /* Add the first series to the chart. */
    series2 = chart_add_series(chart2, "=Sheet1!$I$2:$I$6", "=Sheet1!$J$2:$J$6");
    /* Set the name for the series instead of the default "Series 1". */
    chart_series_set_name(series2, "FCFS");


    series2 = chart_add_series(chart2, "=Sheet1!$I$2:$I$6", "=Sheet1!$K$2:$K$6");
    chart_series_set_name(series2, "RR");

    series2 = chart_add_series(chart2, "=Sheet1!$I$2:$I$6", "=Sheet1!L$2:$L$6");
    chart_series_set_name(series2, "PS");

    series2 = chart_add_series(chart2, "=Sheet1!$I$2:$I$6", "=Sheet1!$M$2:$M$6");
    chart_series_set_name(series2, "SJF");

    /* Add a chart title and some axis labels. */
    chart_title_set_name(chart2, "Waiting time and Avg. Waiting Time");
    chart_axis_set_name(chart->y_axis, "Time (ms)");
    chart_axis_set_name(chart->x_axis, "Process ID");

    worksheet_insert_chart(worksheet, CELL("I9"), chart2);

   return workbook_close(workbook);
}