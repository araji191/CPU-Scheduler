/*
* read_input.h
*
* This module contains functions for reading process scheduling input data from a file.
* It parses process information (name, arrival time, burst time) and a quantum value,
* storing them in an array of Process structures.
*/

#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

/*
* read_input_file
*
* Purpose:
*   Reads process scheduling data from a file, including a quantum value, and
*   stores them in the given Process array.
*
* Inputs:
*   - filename: Represents the input file containing process data.
*   - processes: An array of Process structures to be filled with read data.
*   - num_processes: Pointer to store the number of processes read.
*   - quantum: Pointer to store the quantum value (for Round Robin).
*
* Output:
*   int: Returns 1 for success, 0 on failure (in case of file opening/reading error).
*
* Assumptions:
*   - Input file follows correct format
*   - The given processes array has sufficient capacity for all processes in the file.
*   - Process name doesn't exceed 9 characters.
*/
int read_input_file(const char *filename, Process processes[], int *num_processes, int *quantum);
int read_standard_input(Process processes[], int *num_processes, int *quantum);

#endif
