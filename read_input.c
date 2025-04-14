/*
* read_input.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "process.h"
#include "read_input.h"
#include "constants.h"

int is_valid_process_name(const char *name);

int parse_process_line(char *line, Process *p) {
    char name[32];
    int arrival, burst;
    if (sscanf(line, "%s %d %d", name, &arrival, &burst) != 3) return 0;

    if (!is_valid_process_name(name) || strlen(name) > MAX_PROCESS_NAME_LEN ||
        arrival < 0 || arrival > MAX_ARRIVAL_TIME ||
        burst <= 0 || burst > MAX_BURST_TIME) return 0;

    strcpy(p->name, name);
    p->arrival_time = arrival;
    p->burst_time = burst;
    p->remaining_time = burst;
    return 1;
}

int is_valid_process_name(const char *name) {
    for (int i = 0; name[i]; i++) if (!isalnum(name[i])) return 0;
    return 1;
}

int read_file_input(const char *filename, Process processes[], int *num_processes, int *quantum) {
    FILE *file = fopen(filename, "r");
    if (!file) return perror("Error opening file"), 0;

    char line[100];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "END", 3) == 0) break;
        if (index >= MAX_PROCESSES || !parse_process_line(line, &processes[index])) {
            printf("Error: Invalid input or process limit exceeded.\n");
            fclose(file);
            return 0;
        }
        index++;
    }

    if (fgets(line, sizeof(line), file)) {
        *quantum = atoi(line);
        if (*quantum <= 0 || *quantum > MAX_BURST_TIME) {
            printf("Error: Invalid quantum size.\n");
            fclose(file);
            return 0;
        }
    } else {
        printf("Error: Missing quantum time after END.\n");
        fclose(file);
        return 0;
    }

    *num_processes = index;
    fclose(file);
    return 1;
}

int read_standard_input(Process processes[], int *num_processes, int *quantum) {
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", num_processes);
    if (*num_processes <= 0 || *num_processes > MAX_PROCESSES) return printf("Error: Invalid number.\n"), 0;

    printf("Enter process details (Name ArrivalTime BurstTime):\n");
    for (int i = 0; i < *num_processes; i++) {
        char name[32]; int arrival, burst;
        scanf("%s %d %d", name, &arrival, &burst);
        if (!is_valid_process_name(name) || strlen(name) > MAX_PROCESS_NAME_LEN ||
            arrival < 0 || arrival > MAX_ARRIVAL_TIME ||
            burst <= 0 || burst > MAX_BURST_TIME)
            return printf("Error: Invalid input for '%s'.\n", name), 0;
        strcpy(processes[i].name, name);
        processes[i].arrival_time = arrival;
        processes[i].burst_time = burst;
        processes[i].remaining_time = burst;
    }

    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", quantum);
    if (*quantum <= 0 || *quantum > MAX_BURST_TIME) return printf("Error: Invalid quantum.\n"), 0;

    return 1;
}
