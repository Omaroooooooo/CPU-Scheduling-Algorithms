# CPU Scheduling Algorithms
This project is a simulation of various scheduling algorithms for cpu processes. It includes a queue data structure implementation with enqueue, dequeue, and peek functions to store processes in the ready state waiting for the cpu to become idle.

To run the program, simply compile with *make* and run the compiled scheduler.
```bash
make
./scheduler
```
Input the processes data like their arrival times, burst times, and priorities, and choose the algorithm. The program will output the schedule using that algorithm along with statistics like waiting times and turnaround times for each process and their averages.
