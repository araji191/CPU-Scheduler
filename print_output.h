/*
* print_output.h
*
* This module provides functions for displaying CPU scheduling results to the user.
* This includes: Detailed process metrics (arrival, burst, completion, turnaround, and waiting times),
* average turnaround and waiting times, and a Gantt chart of the schedule.
*/
#ifndef PRINT_OUTPUT_H
#define PRINT_OUTPUT_H

#include "process.h"
#include <stdio.h>

/*
* print_results
*
* Purpose:
*   Prints a formatted table of process scheduling results and calculates/prints
*   average turnaround and waiting times for a given scheduling algorithm.
*
* Inputs:
*   - processes: An array of Process structures containing scheduling results.
*   - n: Number of processes in the array.
*   - algorithm: Represents the scheduling algorithm used (for display purposes).
*
* Output:
*   - void: Results are printed directly to the screen.
*
* Assumptions:
*   - All process fields are initialized.
*/
void print_results(Process processes[], int n, const char* algorithm,
                   GanttInterval *intervals, int interval_count);

/*
* gantt
*
* Purpose:
*   Generates and prints a Gantt chart that visualizes the process schedule.
*
* Inputs:
*   - processes: An array of Process structures containing scheduling results.
*   - n: Number of processes in the array.
*
* Output:
*   - void: Gantt chart is printed to the screen.
*
* Assumptions:
*   - Processes are in order of execution.
*   - Timing fields are properly initialized.
*/
void print_gantt_chart(FILE *output, Process *processes, int num_processes, GanttInterval *intervals, int interval_count);
void print_legend();
void print_output(FILE *output, const char *format, ...);
void print_nonp_gantt_chart(FILE *output, Process *processes, int num_processes);

#endif
