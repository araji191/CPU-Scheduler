/* cpu_scheduler.c */
#include "algorithms.h"
#include "process.h"
#include "print_output.h"
#include "read_input.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int n, quantum;
    Process processes[MAX_PROCESSES], temp[MAX_PROCESSES];
    if (argc == 2) {
        char filepath[200];
        snprintf(filepath, sizeof(filepath), "testcases/%s", argv[1]);
        if (!read_file_input(filepath, processes, &n, &quantum)) {
            printf("Failed to read input file: %s\n", filepath);
            return 1;
        }
        printf("\nSuccessfully read from %s!\n", filepath);

    } else if (argc == 1) {
        if (!read_standard_input(processes, &n, &quantum)) {
            printf("Failed to read standard input.\n");
            return 1;
        }
    } else {
        printf("Usage: %s [input_file]\n", argv[0]);
        return 1;
    }
    
    print_legend();

    // FCFS
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    fcfs(temp, n);
    print_results(temp, n, "First-Come, First-Served (FCFS)");

    // Non-Preemptive SJF
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    sjf_non_preemptive(temp, n);
    print_results(temp, n, "Non-Preemptive Shortest Job First (SJF)");

    // Preemptive SJF
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    sjf_preemptive(temp, n);
    print_results(temp, n, "Preemptive Shortest Job First (SJF)");

    // Round Robin with user-specified quantum
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    round_robin(temp, n, quantum);
    print_results(temp, n, "Round Robin");
    
    return 0;
}