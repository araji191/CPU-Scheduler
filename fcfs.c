#include "algorithms.h"
#include "process.h"
#include <stdio.h>

void fcfs(Process processes[], int n) {
  int time = 0;
  for (int i = 0; i < n; i++) {
    if (time < processes[i].arrival_time)
      time = processes[i].arrival_time;
    
    processes[i].completion_time = time + processes[i].burst_time;
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    time += processes[i].burst_time;
  }
}
