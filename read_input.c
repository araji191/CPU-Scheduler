/*
* read_input.c
*/
#include "read_input.h"

int read_input_file(const char *filename, Process processes[], int *num_processes, int *quantum) {
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

        sscanf(line, "%s %d %d", processes[index].name,
               &processes[index].arrival_time,
               &processes[index].burst_time);

        processes[index].remaining_time = processes[index].burst_time;
        index++;
    }

    // Read quantum after END
    if (fgets(line, sizeof(line), file)) {
        *quantum = atoi(line);
    }

    *num_processes = index;
    fclose(file);
    return 1;
}
