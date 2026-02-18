#include "../header/LCFSNP.h"


static void enqueue_arrivals(process p[], int n, int time, queue_node *queue){
	for (int j = 0; j < n; j++){
		if (p[j].arrival_time == time){
			enqueue(&p[j], queue);
		}
	}
}

void lcfs(process p[], int n, int maxTime, char result[]){
	queue_node *queue = new_queue();
	if (!queue) return;

	process *running = NULL;

	int time = 0;

	while (time < maxTime){
		enqueue_arrivals(p, n, time, queue);

		if (running == NULL) running = dequeue_head(queue);

		if (running != NULL){
			running->time_left--;
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
