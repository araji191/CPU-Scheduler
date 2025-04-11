#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

void fcfs(Process processes[], int n);
void sjf_non_preemptive(Process processes[], int n);
void sjf_preemptive(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);

#endif
