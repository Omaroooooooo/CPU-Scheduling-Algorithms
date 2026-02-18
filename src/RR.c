#include "../header/RR.h"


static void enqueue_arrivals(process p[], int n, int time, queue_node *queue){
	for (int i = 0; i < n; i++){
		if (p[i].arrival_time == time){
			enqueue(&p[i], queue);
		}
	}
}

void robin(process p[], int n, int maxTime, char result[], int quantum){
	queue_node *queue = new_queue();
	if (!queue) return;

	process *running = NULL;
	int q;

	int time = 0;
	
	while (time < maxTime){
		enqueue_arrivals(p, n, time, queue);

		if (running == NULL){ 
			q = quantum;
			running = dequeue(queue);
		}

		if (running != NULL){
			if (q == 0){
				enqueue(running, queue);
				running = dequeue(queue);
				q = quantum;
			}

			running->time_left--;
			q--;
			result[time] = running->id;

			if (running->time_left == 0){
				running->completion_time = time + 1;
				running->turnaround_time = running->completion_time - running->arrival_time;
				running->waiting_time = running->turnaround_time - running->burst_time;
				running = NULL;
			}
		} else {
			result[time] = ' ';
		}
		
		time++;
	}

	result[maxTime] = '\0';
	free_queue(queue);
}
