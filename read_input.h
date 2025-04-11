#ifndef READ_INPUT_H
#define READ_INPUT_H

#include "process.h"

int read_file_input(const char *filename, Process processes[], int *num_processes, int *quantum);
int read_standard_input(Process processes[], int *num_processes, int *quantum);

#endif
