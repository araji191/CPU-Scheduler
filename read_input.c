#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "process.h"
#include "read_input.h"
#include "constants.h"

int is_valid_process_name(const char *name) {
    for (int i = 0; name[i]; i++) {
        if (!isalnum(name[i])) return 0;
    }
    return 1;
}

int read_file_input(const char *filename, Process processes[], int *num_processes, int *quantum) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char line[100];
    int index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "END", 3) == 0)
            break;

        if (index >= MAX_PROCESSES) {
            printf("Error: Maximum number of processes (%d) exceeded.\n", MAX_PROCESSES);
            fclose(file);
            return 0;
        }

        char name[32];
        int arrival, burst;
        if (sscanf(line, "%s %d %d", name, &arrival, &burst) != 3) {
            printf("Error: Invalid input line: %s", line);
            fclose(file);
            return 0;
        }

        if (!is_valid_process_name(name) || strlen(name) > MAX_PROCESS_NAME_LEN) {
            printf("Error: Invalid process name '%s'.\n", name);
            fclose(file);
            return 0;
        }

        if (arrival < 0 || arrival > MAX_ARRIVAL_TIME) {
            printf("Error: Arrival time out of bounds for process '%s'.\n", name);
            fclose(file);
            return 0;
        }

        if (burst <= 0 || burst > MAX_BURST_TIME) {
            printf("Error: Burst time out of bounds for process '%s'.\n", name);
            fclose(file);
            return 0;
        }

        strcpy(processes[index].name, name);
        processes[index].arrival_time = arrival;
        processes[index].burst_time = burst;
        processes[index].remaining_time = burst;
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

    if (*num_processes <= 0 || *num_processes > MAX_PROCESSES) {
        printf("Error: Invalid number of processes.\n");
        return 0;
    }

    printf("Enter process details (Name ArrivalTime BurstTime):\n");
    for (int i = 0; i < *num_processes; i++) {
        char name[32];
        int arrival, burst;
        scanf("%s %d %d", name, &arrival, &burst);

        if (!is_valid_process_name(name) || strlen(name) > MAX_PROCESS_NAME_LEN) {
            printf("Error: Invalid process name '%s'.\n", name);
            return 0;
        }

        if (arrival < 0 || arrival > MAX_ARRIVAL_TIME) {
            printf("Error: Arrival time out of bounds for process '%s'.\n", name);
            return 0;
        }

        if (burst <= 0 || burst > MAX_BURST_TIME) {
            printf("Error: Burst time out of bounds for process '%s'.\n", name);
            return 0;
        }

        strcpy(processes[i].name, name);
        processes[i].arrival_time = arrival;
        processes[i].burst_time = burst;
        processes[i].remaining_time = burst;
    }

    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", quantum);
    if (*quantum <= 0 || *quantum > MAX_BURST_TIME) {
        printf("Error: Invalid quantum size.\n");
        return 0;
    }

    return 1;
}
