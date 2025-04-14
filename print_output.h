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
*   - intervals: Array of GanttInterval structures representing execution time slices.
*   - interval_count: Number of execution intervals in the Gantt chart.
*
* Output:
*   - void: Results are printed directly to the screen.
*
* Assumptions:
*   - All relevant timing fields in each Process structure are initialized.
*   - Execution intervals are in chronological order.
*/
void print_results(Process processes[], int n, const char* algorithm,
                   GanttInterval *intervals, int interval_count);

/*
* print_gantt_chart
*
* Purpose:
*   Generates and prints a Gantt chart to visualize the order and duration of process execution.
*
* Inputs:
*   - output: File pointer to specify output stream (e.g., stdout or file).
*   - processes: Array of Process structures used to match process_id to name.
*   - num_processes: Number of processes in the array.
*   - intervals: Array of GanttInterval structures representing execution slices.
*   - interval_count: Total number of execution intervals.
*
* Output:
*   - void: Gantt chart is printed to the specified output stream.
*
* Assumptions:
*   - Process IDs in GanttInterval match those in the processes array.
*   - Time values are in consistent units.
*/
void print_gantt_chart(FILE *output, Process *processes, int num_processes,
                       GanttInterval *intervals, int interval_count);

/*
* print_legend
*
* Purpose:
*   Prints a legend that maps process IDs to process names for easy interpretation of the Gantt chart.
*
* Inputs:
*   - None
*
* Output:
*   - void: Legend is printed to the screen.
*
* Assumptions:
*   - Process IDs are unique and meaningful to the user.
*/
void print_legend();

/*
* print_output
*
* Purpose:
*   A wrapper around fprintf used to support flexible formatted output across output streams.
*
* Inputs:
*   - output: The output stream to print to (e.g., stdout, file).
*   - format: Format string (similar to printf).
*   - ...: Variable arguments list.
*
* Output:
*   - void: Formatted text is printed to the given output.
*
* Assumptions:
*   - Format string follows standard printf conventions.
*/
void print_output(FILE *output, const char *format, ...);

/*
* print_nonp_gantt_chart
*
* Purpose:
*   Prints a simplified Gantt chart for non-preemptive scheduling algorithms,
*   assuming uninterrupted process execution.
*
* Inputs:
*   - output: Output stream to print to.
*   - processes: Array of Process structures.
*   - num_processes: Number of processes to display.
*
* Output:
*   - void: Gantt chart is printed directly to the output stream.
*
* Assumptions:
*   - Processes are sorted in the order of execution.
*   - Timing fields (start, completion time) are initialized.
*/
void print_nonp_gantt_chart(FILE *output, Process *processes, int num_processes);

#endif
