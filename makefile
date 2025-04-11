all: cpu_scheduler

cpu_scheduler: cpu_scheduler.o fcfs.o pre_sjf.o nonpre_sjf.o round_robin.o read_input.o process.h algorithms.h print_output.o
	gcc -o cpu_scheduler cpu_scheduler.o fcfs.o pre_sjf.o nonpre_sjf.o round_robin.o read_input.o print_output.o

cpu_scheduler.o: cpu_scheduler.c
	gcc -c cpu_scheduler.c

read_input.o: read_input.c
	gcc -c read_input.c

fcfs.o: fcfs.c
	gcc -c fcfs.c

pre_sjf.o: pre_sjf.c
	gcc -c pre_sjf.c

print_output.o: print_output.c
	gcc -c print_output.c

nonpre_sjf.o: nonpre_sjf.c
	gcc -c nonpre_sjf.c

round_robin.o: round_robin.c
	gcc -c round_robin.c

clean:
	rm -f *.o *.c~ *.h~  cpu_scheduler
