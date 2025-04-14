#include <stdio.h>
#include <string.h>
#include "print_output.h"
#include <stdarg.h>

void print_legend() {
    printf("\nLegend\n");
    printf("----------------------\n");
    printf("AT = Arrival Time\n");
    printf("BT = Burst Time\n");
    printf("CT = Completion Time\n");
    printf("TAT = Turnaround Time\n");
    printf("WT = Wait Time\n");
}

void print_results(Process processes[], int n, const char* algorithm,
                   GanttInterval *intervals, int interval_count) {
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

    // === Print Gantt Chart ===
    if (strcmp(algorithm, "First-Come, First-Served (FCFS)") == 0 ||
        strcmp(algorithm, "Non-preemptive Shortest Job First (SJF)") == 0 ||
	      strcmp(algorithm, "Preemptive Shortest Job First (SJF)") == 0 ||
	      strcmp(algorithm, "Round Robin (RR)") == 0 && intervals != NULL) {
          print_gantt_chart(stdout, processes, n, intervals, interval_count);
    } else {
        printf("Gantt chart not available for this algorithm or data.\n");
    }
}

void print_output(FILE *output, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(output, format, args);
  va_end(args);
}

void print_gantt_chart(FILE *output, Process *processes, int num_processes, GanttInterval *intervals, int interval_count) {
  print_output(output, "Gantt Chart:\n");

  // Print processes with their burst times
  for (int i = 0; i < interval_count; i++) {
    print_output(output, "| P%d ", intervals[i].process_id);
    for (int j = intervals[i].start_time; j < intervals[i].end_time; j++) {
      print_output(output, "-");
    }
  }
  print_output(output, "|\n");


  // Print timeline
  print_output(output, "%d", intervals[0].start_time);
  for (int i = 0; i < interval_count; i++) {
    int duration = intervals[i].end_time - intervals[i].start_time;
    print_output(output, "%*d", duration + 5, intervals[i].end_time);
  }
  print_output(output, "\n");  
}
