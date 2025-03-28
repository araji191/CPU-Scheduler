/* main.c */
#include "schedulers.h"
#include <stdio.h>

void print_results(Process processes[], int n, const char* algorithm) {
    printf("\n=== %s ===\n", algorithm);
    printf("Name\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].name, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n], temp[n];
    printf("Enter process details (Name ArrivalTime BurstTime):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", processes[i].name, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
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

    // Round Robin (Time Quantum = 4)
    for (int i = 0; i < n; i++) temp[i] = processes[i];
    round_robin(temp, n, 4);
    print_results(temp, n, "Round Robin (Quantum = 4)");

    return 0;
}
