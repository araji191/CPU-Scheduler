all: main

main: main.o fcfs.o sjf.o rr.o
	gcc -o main main.o fcfs.o sjf.o rr.o

main.o: main.c
	gcc -c main.c

fcfs.o: fcfs.c
	gcc -c fcfs.c

sjf.o: sjf.c
	gcc -c sjf.c

rr.o: rr.c
	gcc -c rr.c

clean:
	rm -f *.o *.c~ *.h~  main
