#include "process.h"
#include <stdbool.h>

void round_robin(Process processes[], int n, int quantum, GanttInterval intervals[], int *interval_count) {
    int time = 0, completed = 0;
    int queue[1000];  // generously sized
    int front = 0, rear = 0;
    bool in_queue[n];
    *interval_count = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        in_queue[i] = false;
    }

    // Start with first arrivals
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }

    while (completed < n) {
        if (front == rear) {
            // No process is in queue — find next arrival
            int next_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && processes[i].remaining_time > 0) {
                    if (processes[i].arrival_time < next_arrival)
                        next_arrival = processes[i].arrival_time;
                }
            }

            // Jump time forward
            time = next_arrival;
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && processes[i].arrival_time <= time) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++];
        Process *p = &processes[idx];

        int exec_time = (p->remaining_time > quantum) ? quantum : p->remaining_time;

        // Add interval to Gantt chart
        if (*interval_count == 0 || intervals[*interval_count - 1].process_id != p->process_id) {
            intervals[*interval_count].start_time = time;
            intervals[*interval_count].end_time = time + exec_time;
            intervals[*interval_count].process_id = p->process_id;
            (*interval_count)++;
        } else {
            intervals[*interval_count - 1].end_time += exec_time;
        }

        time += exec_time;
        p->remaining_time -= exec_time;

        // Check for new arrivals during execution
        for (int i = 0; i < n; i++) {
            if (!in_queue[i] && processes[i].arrival_time <= time) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }

        if (p->remaining_time > 0) {
            queue[rear++] = idx;  // put back into queue
        } else {
            p->completion_time = time;
            p->turnaround_time = time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            completed++;
        }
    }
}
