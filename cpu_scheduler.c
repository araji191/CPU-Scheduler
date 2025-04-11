/* main.c */
#include "algorithms.h"
#include "process.h"
#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n], temp[n];
    printf("Enter process details (Name ArrivalTime BurstTime):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", processes[i].name, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Get time quantum for Round Robin
    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", &quantum);

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
