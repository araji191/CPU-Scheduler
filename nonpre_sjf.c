#include "algorithms.h"
#include "process.h"

#include <stdio.h>
#include <limits.h>

void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int completed = 0, time = 0;
    int is_completed[n];
    *interval_count = 0;

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        // Find the shortest job that's arrived
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] &&
                processes[i].arrival_time <= time &&
                processes[i].burst_time < min_bt) {
                min_bt = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;  // No process available yet
            continue;
        }

        // Record Gantt interval
        intervals[*interval_count].start_time = time;
        intervals[*interval_count].end_time = time + processes[idx].burst_time;
        intervals[*interval_count].process_id = processes[idx].process_id;
        (*interval_count)++;

        // Update stats
        time += processes[idx].burst_time;
        processes[idx].completion_time = time;
        processes[idx].turnaround_time = time - processes[idx].arrival_time;
        processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

        is_completed[idx] = 1;
        completed++;
    }
}
