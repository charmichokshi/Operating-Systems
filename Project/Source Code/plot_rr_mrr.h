//Program - This header file contains comparison plot of Round robin and modified round robin
#include <stdio.h>
#include <stdlib.h>
#include "xlsxwriter.h"

void write_worksheet_data_cmp(lxw_worksheet *worksheet, lxw_format *bold) {

    int row, col=1, i;

	FILE *fp1, *fp2;

    fp1 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/rr_cmp_data.txt", "r");
    fp2 = fopen("/home/charmi/Desktop/OS PROJECT/plot_data/mrr_cmp_data.txt", "r");

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
    

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);

    uint8_t data1[4];
    uint8_t data2[4];


	for (i = 0; i < 4; i++)
    {
		fscanf(fp1, "%d\n", &data1[i]);
        fscanf(fp2, "%d\n", &data2[i]);
	}

    worksheet_write_string(worksheet, CELL("A1"), "Process", bold);
    worksheet_write_string(worksheet, CELL("A2"), "Avg WT", bold);
    worksheet_write_string(worksheet, CELL("A3"), "Avg TT", bold);
    worksheet_write_string(worksheet, CELL("A4"), "Context Switch", bold);
    worksheet_write_string(worksheet, CELL("A5"), "Throughput", bold);     

    worksheet_write_string(worksheet, CELL("B1"), "RR", NULL);
    worksheet_write_string(worksheet, CELL("C1"), "Modified RR", NULL);

    for (row = 0; row < 4; row++) 
    {
            worksheet_write_number(worksheet, row+1, 1, data1[row] , NULL);
            worksheet_write_number(worksheet, row+1, 2, data2[row] , NULL); 
    }
}

int plot_rr_mrr() 
{
    lxw_workbook     *workbook  = new_workbook("/home/charmi/Desktop/OS PROJECT/plot/plot_rr_mrr_cmp.xlsx");
    lxw_worksheet    *worksheet = workbook_add_worksheet(workbook, NULL);
    lxw_chart_series *series;

    /* Add a bold format to use to highlight the header cells. */
    lxw_format *bold = workbook_add_format(workbook);
    format_set_bold(bold);

    /* Write some data for the chart. */
    write_worksheet_data_cmp(worksheet, bold);
    lxw_chart *chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);

    /* Add the first series to the chart. */
    series = chart_add_series(chart, "=Sheet1!$A$2:$A$5", "=Sheet1!$B$2:$B$5");
    /* Set the name for the series instead of the default "Series 1". */
    chart_series_set_name(series, "RR");


    series = chart_add_series(chart, "=Sheet1!$A$2:$A$5", "=Sheet1!$C$2:$C$5");
	chart_series_set_name(series, "Modified RR");

    /* Add a chart title and some axis labels. */
    chart_title_set_name(chart, "Comparision of RR and Modified RR");
    chart_axis_set_name(chart->y_axis, "Time (ms)");

    worksheet_insert_chart(worksheet, CELL("A8"), chart);

   return workbook_close(workbook);
}