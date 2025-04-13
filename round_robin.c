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

#include <stdio.h>

void round_robin(Process processes[], int n, int quantum) {
    int time = 0, completed = 0, front = 0, rear = 0;
    int queue[100], visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    int remaining[n];
    for (int i = 0; i < n; i++) remaining[i] = processes[i].burst_time;

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int idx = queue[front++];
        if (remaining[idx] > quantum) {
            time += quantum;
            remaining[idx] -= quantum;
        } else {
            time += remaining[idx];
            remaining[idx] = 0;
            completed++;
            processes[idx].completion_time = time;
            processes[idx].turnaround_time = time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }

        // Check and enqueue newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrival_time <= time && remaining[i] > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-add current process if it's not done
        if (remaining[idx] > 0)
            queue[rear++] = idx;

        // If queue is empty but there are still processes, jump time to next arrival
        if (front == rear && completed < n) {
            for (int i = 0; i < n; i++) {
                if (remaining[i] > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    time = processes[i].arrival_time;
                    break;
                }
            }
        }
    }
}
