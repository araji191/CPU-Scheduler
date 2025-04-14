/*
* cpu_scheduler.c
*
* Main driver for running and comparing scheduling algorithms:
* FCFS, SJF (non-preemptive and preemptive), and Round Robin.
*/

#include "algorithms.h"
#include "process.h"
#include "print_output.h"
#include "read_input.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Copies original process list to a new array and assigns process IDs
void prepare_processes(Process dest[], Process src[], int n);

/*
* main
*
* Purpose:
*   Coordinates the CPU scheduling simulation by reading process data,
*   running all scheduling algorithms on the same set of processes,
*   and displaying the results.
*
* Inputs:
*   - argc: Argument counter.
*   - argv: Argument vector.
*
* Output:
*   - int: Returns 0 if successful, 1 if there's an error.
*
* Assumptions:
*   - If reading from a file, file is in 'testcases' folder.
*   - Number of processes is under or equal to maximum.
*
* Limitations:
*   - Fixed process limit.
*/
int main(int argc, char *argv[]) {
    int n, quantum;
    Process processes[MAX_PROCESSES], temp[MAX_PROCESSES];
    GanttInterval intervals[MAX_INTERVALS];
    int interval_count;

    // === Input Handling ===
    if (argc == 2) {
        char filepath[200];
        snprintf(filepath, sizeof(filepath), "testcases/%s", argv[1]);
        if (!read_file_input(filepath, processes, &n, &quantum)) {
            printf("Failed to read input file: %s", filepath);
            return 1;
        }
    } else if (argc == 1) {
        if (!read_standard_input(processes, &n, &quantum)) return 1;
    } else {
        printf("Usage: %s [input_file]", argv[0]);
        return 1;
    }

    //FCFS, SJF (non-preemptive and preemptive)
    struct {
        char *name;
        void (*func)(Process[], int, GanttInterval[], int *);
    } algos[] = {
        {"First-Come, First-Served (FCFS)", fcfs},
        {"Non-preemptive Shortest Job First (SJF)", sjf_non_preemptive},
        {"Preemptive Shortest Job First (SJF)", sjf_preemptive}
    };

    print_legend();

    for (int i = 0; i < 3; i++) {
        interval_count = 0;
        prepare_processes(temp, processes, n);              
        algos[i].func(temp, n, intervals, &interval_count);
        print_results(temp, n, algos[i].name, intervals, interval_count); // Output results
    }

    interval_count = 0;
    prepare_processes(temp, processes, n);
    round_robin(temp, n, quantum, intervals, &interval_count);
    print_results(temp, n, "Round Robin (RR)", intervals, interval_count);

    return 0;
}

void prepare_processes(Process dest[], Process src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].process_id = i + 1;
    }
}
