/*
* process.h
*
* This file defines the Process structure used to represent 
* a process in a scheduling system. The structure stores all relevant
* information about a process, including its timing metrics
* (arrival, burst, completion, waiting, and turnaround times) for
* scheduling algorithms.
*/

#ifndef PROCESS_H
#define PROCESS_H

/*
* Process
*
* Purpose:
*   Structure that represents a process in a scheduling system, storing all necessary timing
*   information for scheduling algorithms like FCFS, SJF, Round Robin.
*
* Fields:
*   - name: A string that holds an identifier for the process.
*   - arrival_time: The time at which the process arrives in the ready queue.
*   - burst_time: The total CPU time required by the process to complete execution.
*   - remaining_time: The remaining CPU time needed for completion.
*   - completion_time: The time at which the process completes execution.
*   - waiting_time: The total time the process spends waiting in the ready queue.
*   - turnaround_time: The total time from arrival to completion (waiting_time + burst_time).
*/
typedef struct Process {
    char name[10];
    int process_id;          // ✅ For unique ID tracking in Gantt charts
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;       // ✅ Time when process first gets CPU
    int started;             // ✅ Boolean: whether process started (for response time)
} Process;

typedef struct {
    int process_id;
    int start_time;
    int end_time;
} GanttInterval;

#endif
