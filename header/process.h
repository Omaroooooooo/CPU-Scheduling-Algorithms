#ifndef PROCESS_H
#define PROCESS_H

typedef struct _process {
	int arrival_time;
	int burst_time;
	int time_left;
	int waiting_time;
	int completion_time;
	int turnaround_time;
	int priority;
	char id;
} process;



#endif				
