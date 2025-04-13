#include "process.h"
#include "algorithms.h"
#include <limits.h>

void initialize_completion_flags(int is_completed[], int n);
int select_shortest_non_preemptive_process(Process processes[], int is_completed[], int n, int time);
void update_gantt_chart_non_preemptive(GanttInterval intervals[], int *interval_count, Process p, int start_time);
void finalize_non_preemptive_process(Process *p, int end_time);

void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int completed = 0, time = 0;
    int is_completed[n];
    *interval_count = 0;

    initialize_completion_flags(is_completed, n);

    while (completed < n) {
        int idx = select_shortest_non_preemptive_process(processes, is_completed, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        update_gantt_chart_non_preemptive(intervals, interval_count, processes[idx], time);

        time += processes[idx].burst_time;
        finalize_non_preemptive_process(&processes[idx], time);
        is_completed[idx] = 1;
        completed++;
    }
}


void initialize_completion_flags(int is_completed[], int n) {
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
}

int select_shortest_non_preemptive_process(Process processes[], int is_completed[], int n, int time) {
    int idx = -1, min_bt = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!is_completed[i] &&
            processes[i].arrival_time <= time &&
            processes[i].burst_time < min_bt) {
            min_bt = processes[i].burst_time;
            idx = i;
        }
    }

    return idx;
}

void update_gantt_chart_non_preemptive(GanttInterval intervals[], int *interval_count, Process p, int start_time) {
    intervals[*interval_count].start_time = start_time;
    intervals[*interval_count].end_time = start_time + p.burst_time;
    intervals[*interval_count].process_id = p.process_id;
    (*interval_count)++;
}

void finalize_non_preemptive_process(Process *p, int end_time) {
    p->completion_time = end_time;
    p->turnaround_time = end_time - p->arrival_time;
    p->waiting_time = p->turnaround_time - p->burst_time;
}
