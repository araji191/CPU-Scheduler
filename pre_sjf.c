#include "process.h"
#include <limits.h>
#include <stdbool.h>

static int find_shortest_remaining(Process processes[], int n, int time) {
    int idx = -1, min_rt = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_rt) {
            min_rt = processes[i].remaining_time;
            idx = i;
        }
    }
    return idx;
}

static void update_interval(GanttInterval intervals[], int *interval_count, int pid, int time) {
    if (*interval_count == 0 || intervals[*interval_count - 1].process_id != pid) {
        intervals[*interval_count] = (GanttInterval){time, time + 1, pid};
        (*interval_count)++;
    } else {
        intervals[*interval_count - 1].end_time++;
    }
}

void sjf_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int time = 0, completed = 0;
    *interval_count = 0;
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
    }

    while (completed < n) {
        int idx = find_shortest_remaining(processes, n, time);
        if (idx == -1) { time++; continue; }

        Process *p = &processes[idx];
        if (!p->started) {
            p->started = 1;
            p->response_time = time - p->arrival_time;
        }

        update_interval(intervals, interval_count, p->process_id, time);
        p->remaining_time--;
        if (p->remaining_time == 0) {
            p->completion_time = ++time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            completed++;
        } else time++;
    }
}
