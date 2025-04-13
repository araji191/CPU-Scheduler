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

void prepare_processes(Process dest[], Process src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].process_id = i + 1;
    }
}

int main(int argc, char *argv[]) {
    int n, quantum;
    Process processes[MAX_PROCESSES], temp[MAX_PROCESSES];
    GanttInterval intervals[MAX_INTERVALS];
    int interval_count;

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

    struct { char *name; void (*func)(Process[], int, GanttInterval[], int *); } algos[] = {
        {"FCFS", fcfs},
        {"Non-preemptive SJF", sjf_non_preemptive},
        {"Preemptive SJF", sjf_preemptive}
    };

    for (int i = 0; i < 3; i++) {
        interval_count = 0;
        prepare_processes(temp, processes, n);
        algos[i].func(temp, n, intervals, &interval_count);
        print_results(temp, n, algos[i].name, intervals, interval_count);
    }

    interval_count = 0;
    prepare_processes(temp, processes, n);
    round_robin(temp, n, quantum, intervals, &interval_count);
    print_results(temp, n, "Round Robin", intervals, interval_count);

    return 0;
}
