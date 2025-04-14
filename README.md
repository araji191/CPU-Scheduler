# CPU Scheduler Simulator

## Introduction

The CPU Scheduler Simulator is a software tool designed to evaluate and compare the performance of multiple CPU scheduling algorithms. The simulator calculates and displays the average waiting time and turnaround time for each algorithm, allowing users to compare their efficiency under different scenarios. This project helps students and professionals understand the trade-offs between various scheduling policies and how they impact system performance.

By simulating different scheduling algorithms with the same set of processes, this tool provides valuable insights into how each algorithm handles process execution, offering a clear comparison of their advantages and disadvantages in different scenarios. The simulator processes input data representing processes with arrival times and burst times, then computes key performance metrics that are essential for evaluating scheduling efficiency.

### Implemented Algorithms

The simulator implements four widely-used CPU scheduling algorithms:

1. **First-Come, First-Served (FCFS)** - Processes are executed in the order they arrive in the ready queue.
2. **Non-preemptive Shortest Job First (SJF)** - The process with the shortest burst time is selected for execution first. Once a process starts, it runs to completion.
3. **Preemptive Shortest Job First (SJF)** - Similar to non-preemptive SJF, but the currently running process can be preempted if a new process arrives with a shorter remaining time.
4. **Round Robin (RR)** - Each process is assigned a fixed time slice (quantum). If a process doesn't complete within its time slice, it's placed back in the ready queue.

## Inputs

The simulator accepts input either from a text file or standard input. The input should provide process details in the following format:

```
[Process Name] [Arrival Time] [Burst Time]
```

Where:
- **Process Name**: A string identifier for the process (max 4 characters)
- **Arrival Time**: When the process arrives in the ready queue (integer)
- **Burst Time**: Time required to complete the process (integer)

For file input, the format should be:
```
P1 0 5
P2 1 3
P3 2 8
P4 3 6
END
2
```

The `END` marker indicates the end of process information, and the last number (2 in this example) specifies the time quantum for the Round Robin algorithm.

## Valid Solution

For each algorithm, the simulator produces the following outputs:
- **Completion Time**: When a process finishes its execution
- **Turnaround Time**: Total time taken from arrival to completion (Completion Time - Arrival Time)
- **Waiting Time**: Time spent waiting in the ready queue (Turnaround Time - Burst Time)

The simulator then calculates and displays the average turnaround time and average waiting time for each algorithm, allowing for easy comparison.

### Example Output

```
Legend
----------------------
AT = Arrival Time
BT = Burst Time
CT = Completion Time
TAT = Turnaround Time
WT = Wait Time

=== First-Come, First-Served (FCFS) ===
Name	AT	BT	CT	TAT	WT
P1	0	5	5	5	0
P2	1	3	8	7	4
P3	2	8	16	14	6
P4	3	6	22	19	13

Average Turnaround Time: 11.25
Average Waiting Time: 5.75
Gantt Chart:
| P1 -----| P2 ---| P3 --------| P4 ------|
0         5       8           16         22

=== Non-preemptive Shortest Job First (SJF) ===
Name	AT	BT	CT	TAT	WT
P1	0	5	5	5	0
P2	1	3	8	7	4
P3	2	8	22	20	12
P4	3	6	14	11	5

Average Turnaround Time: 10.75
Average Waiting Time: 5.25
Gantt Chart:
| P1 -----| P2 ---| P4 ------| P3 --------|
0         5       8         14           22

=== Preemptive Shortest Job First (SJF) ===
Name	AT	BT	CT	TAT	WT
P1	0	5	8	8	3
P2	1	3	4	3	0
P3	2	8	22	20	12
P4	3	6	14	11	5

Average Turnaround Time: 10.50
Average Waiting Time: 5.00
Gantt Chart:
| P1 -| P2 ---| P1 ----| P4 ------| P3 --------|
0     1       4        8         14           22

=== Round Robin (RR) ===
Name	AT	BT	CT	TAT	WT
P1	0	5	14	14	9
P2	1	3	11	10	7
P3	2	8	22	20	12
P4	3	6	20	17	11

Average Turnaround Time: 15.25
Average Waiting Time: 9.75
Gantt Chart:
| P1 --| P2 --| P3 --| P1 --| P4 --| P2 -| P3 --| P1 -| P4 --| P3 --| P4 --| P3 --|
0      2      4      6      8     10    11     13    14     16     18     20     22
```

## Project Implementation

### Project Structure and Components

#### Core Data Structures (`process.h`)
- `Process` struct: Contains process details including name, arrival time, burst time, and calculated metrics like completion time, waiting time, and turnaround time.

#### Input Handling (`read_input.h` and `read_input.c`)
- `read_file_input()`: Reads process information from an input file.
- `read_standard_input()`: Accepts process information from user input.
- Validates input parameters such as:
  - Process name format
  - Valid arrival and burst times
  - Time quantum for Round Robin

#### Constants (`constants.h`)
- Defines system constraints like maximum process count, burst time, and arrival time
- Specifies limits for process name length

#### Scheduling Algorithms
- `fcfs.c`: Implementation of First-Come, First-Served algorithm
- `nonpre_sjf.c`: Implementation of Non-preemptive Shortest Job First algorithm
- `pre_sjf.c`: Implementation of Preemptive Shortest Job First algorithm
- `round_robin.c`: Implementation of Round Robin algorithm

#### Output Generation (`print_output.h` and `print_output.c`)
- `print_results()`: Displays scheduling results for each algorithm
- Formats output to show process details and performance metrics

## Gantt Chart Output

For each scheduling algorithm, the simulator generates a visual Gantt Chart that represents the execution timeline of the processes. This is useful for visually inspecting how processes are scheduled and how CPU time is shared or allocated.

Example:
```
Gantt Chart:
| P1 -----| P2 ---| P3 --------| P4 ------|
0        5       8           16         22
```

Each bar represents a process running during a specific time slice. The labels on the bottom indicate the timeline in units of CPU time.

#### Main Program (`cpu_scheduler.c`)
- Handles program execution
- Processes input data
- Executes each scheduling algorithm
- Prints results for comparison

### Scheduling Algorithms

The project implements four classic CPU scheduling algorithms:

#### First-Come, First-Served (FCFS)
- Processes are executed in arrival order
- Simple implementation with no preemption
- May lead to convoy effect where short processes wait behind long ones

#### Non-preemptive Shortest Job First (SJF)
- Selects process with shortest burst time
- Once a process starts, it runs to completion
- Optimal for minimizing average waiting time when all processes arrive simultaneously

#### Preemptive Shortest Job First (SJF)
- Selects process with shortest remaining time
- Current process can be preempted if new shorter process arrives
- Also known as Shortest Remaining Time First (SRTF)

#### Round Robin (RR)
- Each process gets equal time slice (quantum)
- Processes are executed in a circular fashion
- Provides fair CPU distribution but may increase context switching overhead

## Automated Test Execution

A script named `run_tests.sh` is provided to automate testing of the scheduler against multiple input files located in the `testcases` directory.

To run all test cases and store the results in `testcase_results.txt`:
```bash
./run_tests.sh
```

Make sure `cpu_scheduler` is compiled before running the script:
```bash
make
chmod +x run_tests.sh
./run_tests.sh
```

## Usage

```bash
./cpu_scheduler [input_file]
```
It is already assumed that the input file is in the "testcases" directory

Example with file input:
```bash
./cpu_scheduler input1.txt
```

Example with standard input:
```bash
./cpu_scheduler
```

## Requirements

- C compiler (gcc or compatible)
- Standard C libraries
- Make utility (for compilation)

## Compilation

Use the provided Makefile to compile the project:
```bash
make
```

To clean up object files and executables:
```bash
make clean
```

## Input Constraints

- Maximum number of processes: 100
- Maximum burst time: 1000
- Maximum arrival time: 100000
- Maximum process name length: 4 characters
- Process names must be alphanumeric

## Error Handling

The simulator includes comprehensive error checking:

- Input file validation errors
- Process parameter validation
- File access errors
- Memory allocation issues
- Constraint violation detection

If invalid input is detected, appropriate error messages are displayed, and the program terminates gracefully.

## Limitations

- The simulator does not visualize the execution timeline (Gantt chart)
- Limited to the four implemented scheduling algorithms
- Assumes processes are CPU-bound (no I/O operations)
- Does not handle advanced features like process priorities or aging mechanisms