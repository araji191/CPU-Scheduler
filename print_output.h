#ifndef PRINT_OUTPUT_H
#define PRINT_OUTPUT_H

#include "process.h"
#include <stdio.h>

void print_legend();
void print_results(Process processes[], int n, const char* algorithm,
                   GanttInterval *intervals, int interval_count);
void print_gantt_chart(FILE *output, Process *processes, int num_processes, GanttInterval *intervals, int interval_count);
void print_output(FILE *output, const char *format, ...);
void print_nonp_gantt_chart(FILE *output, Process *processes, int num_processes);

#endif
