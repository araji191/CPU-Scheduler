/*
* read_input.h
*
* This module contains functions for reading process scheduling input data from a file.
* It parses process information (name, arrival time, burst time) and a quantum value,
* storing them in an array of Process structures.
*/

#ifndef READ_INPUT_H
#define READ_INPUT_H

#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* read_file_input
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
*   - Input file follows correct format.
*   - The given processes array has sufficient capacity for all processes in the file.
*   - Process name doesn't exceed 9 characters.
*/
int read_file_input(const char *filename, Process processes[], int *num_processes, int *quantum);

/*
* read_standard_input
*
* Purpose:
*   Reads process scheduling data from standard input, including the quantum value,
*   and stores them in the given Process array.
*
* Inputs:
*   - processes: An array of Process structures to be filled with read data.
*   - num_processes: Pointer to store the number of processes read.
*   - quantum: Pointer to store the quantum value (for Round Robin).
*
* Output:
*   int: Returns 1 for success, 0 on failure (e.g., invalid input format).
*
* Assumptions:
*   - Input follows correct format as expected by the program.
*   - The given processes array has sufficient capacity for all entries.
*   - Process name doesn't exceed 9 characters.
*/
int read_standard_input(Process processes[], int *num_processes, int *quantum);

#endif
