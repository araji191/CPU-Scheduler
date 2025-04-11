#include "print_output.h"

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