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

#endif
