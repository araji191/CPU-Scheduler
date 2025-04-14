/*
* process.h
*
* This file defines data structures used to represent processes and Gantt chart
* intervals in a CPU scheduling system. These structures store process timing
* metrics and are essential for both scheduling logic and visual output.
*/

#ifndef PROCESS_H
#define PROCESS_H

/*
* Process
*
* Structure representing a process in the scheduling system.
* Stores all relevant information for calculating scheduling metrics.
*
* Fields:
*   - name: Unique identifier for the process.
*   - process_id: A unique numeric ID for tracking the process in scheduling and visualization.
*   - arrival_time: Time at which the process enters the ready queue.
*   - burst_time: Total CPU time required by the process.
*   - remaining_time: CPU time left (for preemptive scheduling).
*   - completion_time: Time at which the process finishes execution.
*   - waiting_time: Time the process waits in the ready queue.
*   - turnaround_time: Total time from arrival to completion.
*   - response_time: Time from arrival to first CPU allocation.
*   - started: Boolean flag indicating if the process has started (used for response_time tracking).
*/
typedef struct Process {
    char name[10];
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int started;
} Process;

/*
* GanttInterval
*
* Structure representing a time slice in the Gantt chart visualization.
* Used to show which process was running during specific time intervals.
*
* Fields:
*   - process_id: The ID of the process that ran during the interval.
*   - start_time: The time at which the process began execution.
*   - end_time: The time at which the process stopped (or was preempted).
*/
typedef struct {
    int process_id;
    int start_time;
    int end_time;
} GanttInterval;

#endif
