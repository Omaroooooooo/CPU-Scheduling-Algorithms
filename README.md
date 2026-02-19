# CPU Scheduling Algorithms
This project is a simulation of various scheduling algorithms for CPU processes. It includes a queue data structure implementation with enqueue, dequeue, and peek functions to store processes in the ready state waiting for the CPU to become idle.

To run the program, simply compile with *make* and run the compiled scheduler.
```bash
make
./scheduler
```
Input the processes' data like their arrival times, burst times, and priorities, and choose the algorithm. The program will output the schedule using that algorithm, along with statistics like waiting times and turnaround times for each process and their averages.

![Output Schedule and Statistics](/Output.png)

# Algorithms
- [First Come First Serve (FCFS)](#first-come-first-serve-fcfs)
- [Last Come First Serve (LCFS)](#last-come-first-serve-lcfs)
- [Last Come First Serve Preemptive (LCFS-PR)](#last-come-first-serve-preemptive-lcfs-pr)
- [Shortest Job Next (SJN)](#shortest-job-next-sjn)
- [Shortest Remaining Time Next (SRTN)](#shortest-remaining-time-next-srtn)
- [Priorities](#priorities)
- [Round Robin (RR)](#round-robin-rr)
- [Highest Response Ratio Next (HRRN)](#highest-response-ratio-next-hrrn)
- [Multilevel Feedback Queue (MLFQ)](#multilevel-feedback-queue-mlfq)

## First Come First Serve (FCFS)
First Come First Serve, or First In First Out (FIFO), executes the processes in the order they arrived. If two or more processes arrive at the same time, the process with the lower ID is executed first. 

FCFS is a non-preemptive algorithm, which means the process allocated to the CPU will continue running until it ends. It is fairly simple to understand and implement, and it ensures fairness just like in real-life scenarios where first comers are served first. This, however, could lead to bad performance and long waiting times for later arrivals, especially when early arrivals have long burst times.

## Last Come First Serve (LCFS)
LCFS, or LIFO, is the opposite of FCFS, where ready processes are enqueued from the head and dequeued from the head as well, instead of the tail, treating the queue like a stack instead, and ensuring the execution of the most recently arriving processes. It leads to the starvation of early-arriving processes and is rarely used in this form.

## Last Come First Serve Preemptive (LCFS-PR)
The preemptive version of LCFS throws the running process back in the ready queue when a new process arrives. Its goal is to give short jobs a good chance to finish before new arrivals, while long jobs get preempted several times before they can finish. After the last arrival, the remaining processes in the queue are processed in FIFO order.

## Shortest Job Next (SJN)
SJN, or Shortest Job First (SJF), enqueues the arriving processes sorted after their burst times in descending order, resulting in the allocation of the shortest job first to the CPU, and running it till its completion. In case of the same burst times, processes with lower arrival times or lower IDs are executed first, like in FCFS. This algorithm favors short processes and could lead to the starvation of long processes.

## Shortest Remaining Time Next (SRTN)
SRTN, or SRTF, is the preemptive version of SJN, where shorter arriving processes preempt the longer ones, and processes in the queue are ordered according to their remaining times instead of burst times. Both SJN and SRTN help minimize the average waiting time and turnaround time.

## Priorities
In Priority Scheduling, each process is assigned a priority value by the user, and similarly to SJN, processes are sorted according to their priority in the ready queue, and the process with the highest priority is allocated to the CPU. In case of the same priorities, jobs would be processed after FCFS.

In the non-preemptive version, processes will run until they finish, after which a ready process with the highest priority will run next, while in the non-preemptive version, a new arriving process with a higher priority will preempt the running process and take its place.

## Round Robin (RR)
Round Robin works like FCFS, but with a given time window or quantum $\tau$. When the CPU is free, the oldest arriving process in the queue runs for the time of the quantum $\tau$, then it is enqueued back in the queue, if it still has burst time left, and the next process runs for the same time assigned by the quantum. 

Round Robin ensures fairness and even distribution of the processor capacity between processes. The choice of the time window or quantum $\tau$ is an optimization problem. The smaller it is, the more frequently the processes switch, which is a performance overhead. The bigger it is, the more RR approaches FCFS.

## Highest Response Ratio Next (HRRN)
In HRRN, processes are sorted in the queue according to their response ratio, which is calculated by dividing the sum of waiting and burst time by the burst time,   $Response Ratio = \frac{Waiting Time + Burst Time}{Burst Time}$. It is non-preemptive, so after a process finishes its job, the response ratio for each ready process in the queue is calculated, and the highest one is allocated next.

HRRN is also a fair strategy that prefers shorter jobs, but also gives long waiting jobs an advantage, the longer they wait.

## Multilevel Feedback Queue (MLFQ)
In Multilevel Scheduling, processes with different categories (systems, foreground, background, etc.) are stored in multiple queues with different priorities, and each queue has its own scheduling strategy. 

MLFQ is a variant of it, where each queue works with Round Robin, and the time quantum $\tau$ increases as the priority level of the queue decreases. When the CPU is idle, a process is picked from the highest priority queue and runs for the duration of its quantum, after which it gets demoted to the lower priority queue if it is not done.
