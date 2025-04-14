/*
 * fcfs.c
 *
 * This file implements the First-Come, First-Served (FCFS) CPU scheduling algorithm.
 * Processes are executed in the order of their arrival, with no preemption.
 * The implementation calculates completion, turnaround, and waiting times for each process.
 */

#include "algorithms.h"
#include "process.h"
#include <stdio.h>

void fcfs(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int time = 0;
    *interval_count = 0; //Initialize Gantt counter

    for (int i = 0; i < n; i++) {
        //Handle idle CPU time between processes
        if (time < processes[i].arrival_time)
            time = processes[i].arrival_time;

        //Record execution interval for Gantt chart
        intervals[*interval_count].start_time = time;
        intervals[*interval_count].end_time = time + processes[i].burst_time;
        intervals[*interval_count].process_id = processes[i].process_id;
        (*interval_count)++;


        //Calculate process metrics
        processes[i].completion_time = time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        time += processes[i].burst_time; //Advance simulation time
    }
}


