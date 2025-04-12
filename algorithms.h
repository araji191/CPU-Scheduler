#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

void fcfs(Process processes[], int n, GanttInterval intervals[], int *interval_count);
void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count);
void sjf_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count);
void round_robin(Process processes[], int n, int quantum, GanttInterval intervals[], int *interval_count);

#endif
