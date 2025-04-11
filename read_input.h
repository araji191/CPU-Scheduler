#ifndef READ_INPUT_H
#define READ_INPUT_H

#include "process.h"

int read_input_file(const char *filename, Process processes[], int *num_processes, int *quantum);

#endif