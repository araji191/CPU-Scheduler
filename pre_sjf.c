/*
* pre_sjf.c
*
* This file implements the Preemptive Shortest Job First (SJF) CPU scheduling algorithm.
* The scheduler always selects the process with the shortest remaining execution time,
* preempting the current process if a shorter one becomes available.
*/

#include "algorithms.h"
#include "process.h"
#include <limits.h>

void initialize_sjf_processes(Process processes[], int n);
int select_shortest_remaining_process(Process processes[], int n, int time);
void update_gantt_chart_sjf(GanttInterval intervals[], int *interval_count, int process_id, int time);
void finalize_process_if_complete(Process *p, int time, int *completed);

void sjf_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int time = 0, completed = 0;
    *interval_count = 0;

    initialize_sjf_processes(processes, n);

    while (completed < n) {
        int idx = select_shortest_remaining_process(processes, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        Process *p = &processes[idx];

        if (!p->started) {
            p->started = 1;
            p->response_time = time - p->arrival_time;
        }

        update_gantt_chart_sjf(intervals, interval_count, p->process_id, time);

        p->remaining_time--;
        time++;

        finalize_process_if_complete(p, time, &completed);
    }
}

void initialize_sjf_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
    }
}

int select_shortest_remaining_process(Process processes[], int n, int time) {
    int idx = -1, min_rt = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= time &&
            processes[i].remaining_time > 0 &&
            processes[i].remaining_time < min_rt) {
            min_rt = processes[i].remaining_time;
            idx = i;
        }
    }
    return idx;
}

void update_gantt_chart_sjf(GanttInterval intervals[], int *interval_count, int process_id, int time) {
    if (*interval_count == 0 || intervals[*interval_count - 1].process_id != process_id) {
        intervals[*interval_count].start_time = time;
        intervals[*interval_count].end_time = time + 1;
        intervals[*interval_count].process_id = process_id;
        (*interval_count)++;
    } else {
        intervals[*interval_count - 1].end_time++;
    }
}

void finalize_process_if_complete(Process *p, int time, int *completed) {
    if (p->remaining_time == 0) {
        p->completion_time = time;
        p->turnaround_time = time - p->arrival_time;
        p->waiting_time = p->turnaround_time - p->burst_time;
        (*completed)++;
    }
}