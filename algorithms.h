/*
* algorithms.h
*
* This file contains function declarations for four CPU scheduling algorithms:
*   - First-Come, First-Served (FCFS)
*   - Non-Preemptive Shortest Job First (SJF)
*   - Preemptive Shortest Job First (SJF)
*   - Round Robin
*
* Each algorithm schedules an array of Process structures and calculates scheduling
* metrics such as completion time, turnaround time, and waiting time. They also populate
* a Gantt chart represented as an array of GanttInterval structures.
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

/*
* fcfs
*
* Purpose:
*   Implements the First-Come, First-Served scheduling algorithm that executes
*   processes strictly in their order of arrival, without preemption.
*
* Inputs:
*   - processes: An array of Process structures sorted by arrival time.
*   - n: The number of processes in the array.
*   - intervals: An array to store the Gantt chart intervals for process execution.
*   - interval_count: Pointer to store the number of intervals generated.
*
* Output:
*   - void: The processes array is modified in-place with updated timing metrics.
*           The intervals array is filled with Gantt chart data.
*
* Assumptions:
*   - Processes are sorted by arrival time.
*   - Burst times are positive integers.
*/
void fcfs(Process processes[], int n, GanttInterval intervals[], int *interval_count);

/*
* sjf_non_preemptive
*
* Purpose:
*   Implements the Non-Preemptive Shortest Job First scheduling algorithm.
*   At each step, selects the shortest burst time process from the ready queue
*   and runs it to completion.
*
* Inputs:
*   - processes: An array of Process structures to be scheduled.
*   - n: The number of processes in the array.
*   - intervals: An array to store the Gantt chart intervals for process execution.
*   - interval_count: Pointer to store the number of intervals generated.
*
* Output:
*   - void: The processes array is modified in-place with updated timing metrics.
*           The intervals array is filled with Gantt chart data.
*
* Assumptions:
*   - Arrival and burst times are valid and initialized.
*   - Process array has 'n' valid entries.
*
* Limitations:
*   - No special handling for tie-breaking on equal burst times.
*/
void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count);

/*
* sjf_preemptive
*
* Purpose:
*   Implements the Preemptive Shortest Job First scheduling algorithm (a.k.a. Shortest Remaining Time First).
*   Continuously chooses the process with the smallest remaining time among all arrived processes.
*
* Inputs:
*   - processes: An array of Process structures to be scheduled.
*   - n: The number of processes in the array.
*   - intervals: An array to store the Gantt chart intervals for process execution.
*   - interval_count: Pointer to store the number of intervals generated.
*
* Output:
*   - void: The processes array is modified in-place with updated timing metrics.
*           The intervals array is filled with Gantt chart data.
*
* Assumptions:
*   - All process fields are properly initialized.
*   - Remaining time field will be initialized inside the function.
*
* Limitations:
*   - No tie-breaking logic for equal remaining times.
*/
void sjf_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count);

/*
* round_robin
*
* Purpose:
*   Implements the Round Robin scheduling algorithm using a fixed time quantum.
*   Each process is allowed to execute in equal time slices and is cycled
*   through until completion.
*
* Inputs:
*   - processes: An array of Process structures to be scheduled.
*   - n: The number of processes in the array.
*   - quantum: The time slice allocated to each process per turn.
*   - intervals: An array to store the Gantt chart intervals for process execution.
*   - interval_count: Pointer to store the number of intervals generated.
*
* Output:
*   - void: The processes array is modified in-place with updated timing metrics.
*           The intervals array is filled with Gantt chart data.
*
* Assumptions:
*   - Quantum is a positive integer.
*   - Processes are initialized and ready for execution.
*
* Limitations:
*   - Uses a statically sized queue (fixed array size).
*   - Does not include tie-breaking logic for arrival conflicts.
*/
void round_robin(Process processes[], int n, int quantum, GanttInterval intervals[], int *interval_count);

#endif
