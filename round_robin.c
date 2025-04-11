#include "schedulers.h"
#include <stdio.h>

void round_robin(Process processes[], int n, int quantum) {
    int time = 0, completed = 0;
    int queue[n], front = 0, rear = 0;
    int remaining[n];
    for (int i = 0; i < n; i++) {
        remaining[i] = processes[i].burst_time;
    }
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && processes[i].arrival_time <= time) {
                if (remaining[i] > quantum) {
                    time += quantum;
                    remaining[i] -= quantum;
                } else {
                    time += remaining[i];
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time
		    - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time
		      - processes[i].burst_time;
                    remaining[i] = 0;
                    completed++;
                }
            }
        }
    }
}
