#include "process.h"
#include <stdbool.h>

static void enqueue_arrivals(Process processes[], int n, int time, int queue[], int *rear, bool in_queue[]) {
    for (int i = 0; i < n; i++) {
        if (!in_queue[i] && processes[i].arrival_time <= time) {
            queue[(*rear)++] = i;
            in_queue[i] = true;
        }
    }
}

static void record_interval(GanttInterval intervals[], int *interval_count, int pid, int time, int duration) {
    if (*interval_count == 0 || intervals[*interval_count - 1].process_id != pid) {
        intervals[*interval_count] = (GanttInterval){time, time + duration, pid};
        (*interval_count)++;
    } else {
        intervals[*interval_count - 1].end_time += duration;
    }
}

static void advance_to_next_arrival(Process processes[], int n, int *time, int queue[], int *rear, bool in_queue[]) {
    int next_arrival = 1e9;
    for (int i = 0; i < n; i++) {
        if (!in_queue[i] && processes[i].remaining_time > 0 && processes[i].arrival_time < next_arrival) {
            next_arrival = processes[i].arrival_time;
        }
    }
    *time = next_arrival;
    enqueue_arrivals(processes, n, *time, queue, rear, in_queue);
}

void round_robin(Process processes[], int n, int quantum, GanttInterval intervals[], int *interval_count) {
    int time = 0, completed = 0;
    int queue[1000], front = 0, rear = 0;
    bool in_queue[n];
    *interval_count = 0;
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        in_queue[i] = false;
    }
    enqueue_arrivals(processes, n, time, queue, &rear, in_queue);

    while (completed < n) {
        if (front == rear) { advance_to_next_arrival(processes, n, &time, queue, &rear, in_queue); continue; }

        int idx = queue[front++];
        Process *p = &processes[idx];
        int exec_time = (p->remaining_time > quantum) ? quantum : p->remaining_time;

        record_interval(intervals, interval_count, p->process_id, time, exec_time);
        time += exec_time;
        p->remaining_time -= exec_time;
        enqueue_arrivals(processes, n, time, queue, &rear, in_queue);

        if (p->remaining_time > 0) {
            queue[rear++] = idx;
        } else {
            p->completion_time = time;
            p->turnaround_time = time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            completed++;
        }
    }
}
