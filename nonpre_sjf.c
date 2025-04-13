#include "algorithms.h"
#include "process.h"
#include <limits.h>

static int find_shortest_ready_process(Process processes[], int n, int time, int is_completed[]) {
    int idx = -1, min_bt = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!is_completed[i] && processes[i].arrival_time <= time && processes[i].burst_time < min_bt) {
            min_bt = processes[i].burst_time;
            idx = i;
        }
    }
    return idx;
}

static void complete_process(Process *p, int *time) {
    *time += p->burst_time;
    p->completion_time = *time;
    p->turnaround_time = *time - p->arrival_time;
    p->waiting_time = p->turnaround_time - p->burst_time;
}

void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int completed = 0, time = 0;
    int is_completed[n];
    *interval_count = 0;
    for (int i = 0; i < n; i++) is_completed[i] = 0;

    while (completed < n) {
        int idx = find_shortest_ready_process(processes, n, time, is_completed);
        if (idx == -1) { time++; continue; }

        intervals[*interval_count] = (GanttInterval){time, time + processes[idx].burst_time, processes[idx].process_id};
        (*interval_count)++;

        complete_process(&processes[idx], &time);
        is_completed[idx] = 1;
        completed++;
    }
}
