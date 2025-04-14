/*
* nonpre_sjf.c
*
* This file implements the Non-Preemptive Shortest Job First (SJF) CPU scheduling algorithm.
* The scheduler selects the process with the shortest burst time that has arrived,
* and runs it to completion without preemption.
*/

#include "process.h"
#include "algorithms.h"

#include <limits.h>

// Helper function declarations
void initialize_completion_flags(int is_completed[], int n);
int select_shortest_non_preemptive_process(Process processes[], int is_completed[], int n, int time);
void update_gantt_chart_non_preemptive(GanttInterval intervals[], int *interval_count, Process p, int start_time);
void finalize_non_preemptive_process(Process *p, int end_time);

void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int completed = 0, time = 0;
    int is_completed[n];  // Array to track if a process has completed
    *interval_count = 0;

    initialize_completion_flags(is_completed, n);  // Set all process completion flags to 0

    while (completed < n) {
        // Select the process with the shortest burst time that has arrived and is not completed
        int idx = select_shortest_non_preemptive_process(processes, is_completed, n, time);

        if (idx == -1) {
            // If no process is ready, increment time and retry
            time++;
            continue;
        }

        // Log the process execution in the Gantt chart
        update_gantt_chart_non_preemptive(intervals, interval_count, processes[idx], time);

        // Move time forward by the burst time of the selected process
        time += processes[idx].burst_time;

        // Update process statistics after execution
        finalize_non_preemptive_process(&processes[idx], time);

        is_completed[idx] = 1;  // Mark the process as completed
        completed++;  // Increment completed process count
    }
}

void initialize_completion_flags(int is_completed[], int n) {
    // Initialize all process completion flags to 0 (not completed)
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
}

int select_shortest_non_preemptive_process(Process processes[], int is_completed[], int n, int time) {
    int idx = -1, min_bt = INT_MAX;

    // Iterate through processes to find the shortest one that has arrived and is not completed
    for (int i = 0; i < n; i++) {
        if (!is_completed[i] &&
            processes[i].arrival_time <= time &&
            processes[i].burst_time < min_bt) {
            min_bt = processes[i].burst_time;
            idx = i;
        }
    }

    return idx;  // Return index of the selected process or -1 if none are available
}

void update_gantt_chart_non_preemptive(GanttInterval intervals[], int *interval_count, Process p, int start_time) {
    // Record the process's start and end time in the Gantt chart
    intervals[*interval_count].start_time = start_time;
    intervals[*interval_count].end_time = start_time + p.burst_time;
    intervals[*interval_count].process_id = p.process_id;
    (*interval_count)++;  // Move to next interval slot
}

void finalize_non_preemptive_process(Process *p, int end_time) {
    // Compute and store process timing metrics
    p->completion_time = end_time;
    p->turnaround_time = end_time - p->arrival_time;
    p->waiting_time = p->turnaround_time - p->burst_time;
}
