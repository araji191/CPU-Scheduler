#include "schedulers.h"
#include <stdio.h>
#include <limits.h>

void sjf_non_preemptive(Process processes[], int n) {
    int completed = 0, time = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;

    while (completed < n) {
        int min_idx = -1;
        int min_bt = INT_MAX;

        // Find the shortest available job at current time
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= time && 
                processes[i].burst_time < min_bt) {
                min_bt = processes[i].burst_time;
                min_idx = i;
            }
        }

        if (min_idx == -1) {
            // No process available; find the next arrival time
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!is_completed[i] && processes[i].arrival_time < next_arrival) {
                    next_arrival = processes[i].arrival_time;
                }
            }
            time = next_arrival;  // Jump to the next arrival time
            continue;
        }

        // Execute the selected process
        time += processes[min_idx].burst_time;
        processes[min_idx].completion_time = time;
        processes[min_idx].turnaround_time = time - processes[min_idx].arrival_time;
        processes[min_idx].waiting_time = processes[min_idx].turnaround_time - processes[min_idx].burst_time;
        is_completed[min_idx] = 1;
        completed++;
    }
}



void sjf_preemptive(Process processes[], int n) {
    int completed = 0, time = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed < n) {
        int min_idx = -1;
        int min_remaining = INT_MAX;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time &&
                processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining) {
                min_remaining = processes[i].remaining_time;
                min_idx = i;
            }
        }

        if (min_idx == -1) {
            time++;
            continue;
        }

        // Execute the process for 1 unit
        processes[min_idx].remaining_time--;

        // Check if process completed
        if (processes[min_idx].remaining_time == 0) {
            completed++;
            processes[min_idx].completion_time = time + 1;
            processes[min_idx].turnaround_time = 
                processes[min_idx].completion_time - processes[min_idx].arrival_time;
            processes[min_idx].waiting_time = 
                processes[min_idx].turnaround_time - processes[min_idx].burst_time;
        }

        time++;  // Correct position: increment after processing
    }
}
