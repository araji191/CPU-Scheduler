/*
* round_robin.c
*
* This file implements the Round Robin CPU scheduling algorithm.
* It schedules processes by giving each process a fixed time quantum,
* updating process metrics (completion, turnaround, and waiting time)
* accordingly.
*/
#include "algorithms.h"
#include "process.h"

#include <stdbool.h>

void initialize_processes(Process processes[], int n, bool in_queue[]);
void enqueue_initial_processes(Process processes[], int n, int queue[], int *rear, bool in_queue[]);
void enqueue_new_arrivals(Process processes[], int n, int time, int queue[], int *rear, bool in_queue[]);
int handle_idle_time(Process processes[], int n, int *time, int queue[], int *rear, bool in_queue[]);
void execute_process(Process *p, int quantum, int *time, GanttInterval intervals[], int *interval_count);

void round_robin(Process processes[], int n, int quantum, GanttInterval intervals[], int *interval_count) {
    int time = 0, completed = 0;
    int queue[1000];
    int front = 0, rear = 0;
    bool in_queue[n];
    *interval_count = 0;

    initialize_processes(processes, n, in_queue);
    enqueue_initial_processes(processes, n, queue, &rear, in_queue);

    while (completed < n) {
        if (front == rear) {
            handle_idle_time(processes, n, &time, queue, &rear, in_queue);
            continue;
        }

        int idx = queue[front++];
        Process *p = &processes[idx];

	execute_process(p, quantum, &time, intervals, interval_count);
        enqueue_new_arrivals(processes, n, time, queue, &rear, in_queue);

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

void initialize_processes(Process processes[], int n, bool in_queue[]) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        in_queue[i] = false;
    }
}

void enqueue_initial_processes(Process processes[], int n, int queue[], int *rear, bool in_queue[]) {
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            queue[(*rear)++] = i;
            in_queue[i] = true;
        }
    }
}

void enqueue_new_arrivals(Process processes[], int n, int time, int queue[], int *rear, bool in_queue[]) {
    for (int i = 0; i < n; i++) {
        if (!in_queue[i] && processes[i].arrival_time <= time) {
            queue[(*rear)++] = i;
            in_queue[i] = true;
        }
    }
}

int handle_idle_time(Process processes[], int n, int *time, int queue[], int *rear, bool in_queue[]) {
    int next_arrival = 1e9;
    for (int i = 0; i < n; i++) {
        if (!in_queue[i] && processes[i].remaining_time > 0) {
            if (processes[i].arrival_time < next_arrival)
                next_arrival = processes[i].arrival_time;
        }
    }
    if (next_arrival != 1e9) {
        *time = next_arrival;
        enqueue_new_arrivals(processes, n, *time, queue, rear, in_queue);
    }
    return *time;
}

void execute_process(Process *p, int quantum, int *time, GanttInterval intervals[], int *interval_count) {
    int exec_time = (p->remaining_time > quantum) ? quantum : p->remaining_time;

    if (*interval_count == 0 || intervals[*interval_count - 1].process_id != p->process_id) {
        intervals[*interval_count].start_time = *time;
        intervals[*interval_count].end_time = *time + exec_time;
        intervals[*interval_count].process_id = p->process_id;
        (*interval_count)++;
    } else {
        intervals[*interval_count - 1].end_time += exec_time;
    }

    *time += exec_time;
    p->remaining_time -= exec_time;
}