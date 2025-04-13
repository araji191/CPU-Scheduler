/*
* nonpre_sjf.c
*
* This file implements the Non-Preemptive Shortest Job First (SJF) CPU scheduling algorithm.
* The scheduler selects the process with the shortest burst time that has arrived,
* and runs it to completion without preemption.
*/
#include "algorithms.h"
#include "process.h"

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