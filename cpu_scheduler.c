/* 
* cpu_scheduler.c 
*
* Contains the main function of a CPU scheduler that compares four algorithms:
*   - First Come First Served (FCFS)
*   - Non-Preemptive Shortest Job First (SJF)
*   - Preemptive Shortest Job First (SJF)
*   - Round Robin
* 
* The program can read input from a file and run all scheduling algorithms
* on the same set of processes. It then displays the results including
* metrics of each individual process and average turnaround and waiting times.
*/
#include "algorithms.h"
#include "process.h"
#include "print_output"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100

// Declare the file input function (should be defined in read_input.c)
int read_input_file(const char *filename, Process processes[], int *num_processes, int *quantum);

void print_results(Process processes[], int n, const char* algorithm) {
    float avg_tat = 0, avg_wt = 0;
    
    printf("\n=== %s ===\n", algorithm);
    printf("Name\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].name, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
        
        avg_tat += processes[i].turnaround_time;
        avg_wt += processes[i].waiting_time;
    }
    
    avg_tat /= n;
    avg_wt /= n;
    
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

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

    if (argc == 2) {
        // Read from file
        char filepath[200];
        snprintf(filepath, sizeof(filepath), "testcases/%s", argv[1]);
        if (!read_input_file(filepath, processes, &n, &quantum)) {
            printf("Failed to read input file: %s\n", filepath);
            return 1;
        }
    } else if (argc == 1) {
        // Standard input
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