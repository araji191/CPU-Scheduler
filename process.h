#ifndef PROCESS_H
#define PROCESS_H

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
