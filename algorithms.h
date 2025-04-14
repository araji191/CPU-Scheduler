/*
* algorithms.h
*
* This file contains the declerations for 4 CPU scheduling algorithms:
*   - First Come First Served (FCFS)
*   - Non-Preemtive Shortest Job First (SJF)
*   - Preemptive Shortest Job First (SJF)
*   - Round Robin
* Each algorithm takes an array of processes and computes scheduling metrics
* (completion time, turnaround time, waiting time).
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

/*
* fcfs
*
* Purpose:
*   Implements the First-Come, First-Served scheduling algorithm that executes
*   processes in strict arrival order, calculating timing metrics for each process.
*
* Inputs:
*   processes - An array of Process structures to be scheduled (ordered by arrival time).
*   n - Number of processes in the array.
*
* Output:
*   void - The input processes array is modified in-place with updated
*          timing metrics (completion_time, turnaround_time, waiting_time).
*
* Assumptions:
*   - Processes are sorted by arrival time.
*   - Process burst times are positive values.
*/
void fcfs(Process processes[], int n, GanttInterval intervals[], int *interval_count);

/*
* sjf_non_preemptive
*
* Purpose:
*   Implements the Non-Preemptive Shortest Job First scheduling algorithm that selects
*   the process with the shortest burst time and runs it to completion before selecting
*   the next shortest available job.
*
* Inputs:
*   processes - Array of Process structures to be scheduled.
*   n - Number of processes in the array.
*
* Output:
*   void - The input processes array is updated with the proper
*          timing metrics (completion_time, turnaround_time, waiting_time).
*
* Assumptions: 
*   - Process arrival times are properly initialized.
*   - Process burst times are positive values.
*   - Process array contains 'n' processes.
*
* Limitations:
*   - No handling for processes with equal burst times.
*/
void sjf_non_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count);

/*
* sjf_preemptive
*
* Purpose:
*   Implements the Preemptive Shortest Job First scheduling algorithm that selects
*   the process with the shortest remaining time at each scheduling point.
*
* Inputs:
 *   processes - Array of Process structures to be scheduled.
 *   n - Number of processes in the array.
 *
 * Output:
 *   void - The input processes array is modified in-place with updated
 *          timing metrics (completion_time, turnaround_time, waiting_time).
 * 
 * Assumptions:
 *    - Process arrival times are properly initialized
 *    - Process burst times are positive values.
 *    - Process array contains 'n' processes.
 * 
 *  Limitations:
 *   - No error checking for invalid process data.
*/
void sjf_preemptive(Process processes[], int n, GanttInterval intervals[], int *interval_count);

/*
* round_robin
*
* Purpose:
*   Implements the Round Robin scheduling algorithm to schedule processes
*   with a given time quantum, updating their completion, turnaround, 
*   and waiting times.
*
* Inputs:
*   - processes: Array of Process structures to be scheduled.
*   - n: Number of processes in the array.
*   - quantum: Time quantum for Round Robin scheduling.
*
* Output:
*   - void: The input "processes" array is modified with updated timing metrics
*           (completion_time, turnaround_time, waiting_time).
*
* Assumptions:
*   - Processes are initially sorted by arrival time.
*   - Quantum value is a positive number.
*   - Process array contains valid data.
*
* Limitations:
*   - Queue is a fixed-size.
*/
void round_robin(Process processes[], int n, int quantum, GanttInterval intervals[], int *interval_count);

#endif
