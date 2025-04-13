#include "process.h"
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


void sjf_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count) {
    int time = 0, completed = 0;
    int last_pid = -1;
    *interval_count = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = 0;
    }

    while (completed < n) {
        int idx = -1;
        int min_rt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_rt) {
                min_rt = processes[i].remaining_time;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;  // No process is ready, CPU idle
            continue;
        }

        Process *p = &processes[idx];

        if (!p->started) {
            p->started = 1;
            p->response_time = time - p->arrival_time;
        }

        // Update Gantt interval
        if (*interval_count == 0 || intervals[*interval_count - 1].process_id != p->process_id) {
            intervals[*interval_count].start_time = time;
            intervals[*interval_count].end_time = time + 1;
            intervals[*interval_count].process_id = p->process_id;
            (*interval_count)++;
        } else {
            intervals[*interval_count - 1].end_time++;
        }

        p->remaining_time--;
        time++;

        if (p->remaining_time == 0) {
            p->completion_time = time;
            p->turnaround_time = time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            completed++;
        }
    }
}
