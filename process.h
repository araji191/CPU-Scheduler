#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
  char name[10];
  int arrival_time;
  int burst_time;
  int remaining_time;
  int completion_time;
  int waiting_time;
  int turnaround_time;
} Process;

void fcfs(Process processes[], int n);
void sjf_non_preemptive(Process processes[], int n);
void sjf_preemptive(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);

#endif
