#include "schedulers.h"
#include <stdio.h>
#include <limits.h>

void sjf_non_preemptive(Process processes[], int n) {
    int completed = 0, time = 0, min_idx;
    int is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;
    
    while (completed < n) {
        int min_time = INT_MAX;
        min_idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && !is_completed[i] &&
		processes[i].burst_time < min_time) {
                min_time = processes[i].burst_time;
                min_idx = i;
            }
        }
        
        if (min_idx == -1) {
            time++;
            continue;
        }
        
        time += processes[min_idx].burst_time;
        processes[min_idx].completion_time = time;
        processes[min_idx].turnaround_time = processes[min_idx].completion_time
	  - processes[min_idx].arrival_time;
        processes[min_idx].waiting_time = processes[min_idx].turnaround_time
	  - processes[min_idx].burst_time;
        is_completed[min_idx] = 1;
        completed++;
    }
}

void sjf_preemptive(Process processes[], int n) {
    int completed = 0, time = 0, min_idx = -1;
    while (completed < n) {
      int min_time = 1e9;
      for (int i = 0; i < n; i++) {
	if (processes[i].arrival_time <= time &&
	    processes[i].remaining_time > 0 &&
	    processes[i].remaining_time < min_time) {
	  min_time = processes[i].remaining_time;
	  min_idx = i;
	}
      }
      if (min_idx == -1) {
	time++;
	continue;
      }
      processes[min_idx].remaining_time--;
      if (processes[min_idx].remaining_time == 0) {
	completed++;
	processes[min_idx].completion_time = time + 1;
	processes[min_idx].turnaround_time = processes[min_idx].completion_time
	  - processes[min_idx].arrival_time;
	processes[min_idx].waiting_time = processes[min_idx].turnaround_time -
	  processes[min_idx].burst_time;
      }
      time++;
    }
}
