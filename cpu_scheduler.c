#include "algorithms.h"
#include "process.h"
#include "print_output.h"
#include "read_input.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define MAX_INTERVALS 1000

int main(int argc, char *argv[]) {
    int n, quantum;
    Process processes[MAX_PROCESSES], temp[MAX_PROCESSES];

    GanttInterval intervals[MAX_INTERVALS];
    int interval_count;

    if (argc == 2) {
        char filepath[200];
        snprintf(filepath, sizeof(filepath), "testcases/%s", argv[1]);
        if (!read_file_input(filepath, processes, &n, &quantum)) {
            printf("Failed to read input file: %s\n", filepath);
            return 1;
        }
    } else if (argc == 1) {
        printf("Enter number of processes: ");
        scanf("%d", &n);
        printf("Enter process details (Name ArrivalTime BurstTime):\n");
        for (int i = 0; i < n; i++) {
            scanf("%s %d %d", processes[i].name, &processes[i].arrival_time, &processes[i].burst_time);
            processes[i].remaining_time = processes[i].burst_time;
        }

        printf("\nEnter time quantum for Round Robin: ");
        scanf("%d", &quantum);

    } else {
        printf("Usage: %s [input_file]\n", argv[0]);
        return 1;
    }

     // FCFS
    interval_count = 0;
    for (int i = 0; i < n; i++) {
      processes[i].process_id = i + 1; 
      temp[i] = processes[i];
    }
    fcfs(temp, n, intervals, &interval_count);
    print_results(temp, n, "FCFS", intervals, interval_count);

    // Non-Preemptive SJF
    interval_count = 0;
    interval_count = 0;
    for (int i = 0; i < n; i++) {
      temp[i] = processes[i];             // Copy original
      temp[i].process_id = i + 1;         // ✅ Assign ID to the copy (NOT to processes[])
    }

    sjf_non_preemptive(temp, n, intervals, &interval_count);
    print_results(temp, n, "SJF", intervals, interval_count);

    // Preemptive SJF
    interval_count = 0;
    for (int i = 0; i < n; i++) {
      processes[i].process_id = i + 1;
      temp[i] = processes[i];
    }    
    sjf_preemptive(temp, n, intervals, &interval_count);
    print_results(temp, n, "SRTF", intervals, interval_count);

    // Round Robin
    interval_count = 0;
    for (int i = 0; i < n; i++) {
      processes[i].process_id = i + 1;
      temp[i] = processes[i];
    }
    round_robin(temp, n, quantum, intervals, &interval_count);
    print_results(temp, n, "Round Robin", intervals, interval_count);

    return 0;
}
