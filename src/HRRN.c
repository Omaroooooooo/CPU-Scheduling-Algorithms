#include "../header/HRRN.h"
#include <math.h>


void *dequeue_hrrn(int time, queue_node *queue){
	if (queue->next == NULL) return NULL;
	if (queue->next->next == NULL) return dequeue_head(queue);

	float rr;
	float hrr = 0;

	process *proc;
	process *hrr_proc;

	queue_node *hrr_proc_prev = queue;
	queue_node *prev = NULL;
    queue_node *curr = queue;

	while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
		proc = curr->object;
        
		proc->waiting_time = time - proc->arrival_time;
		rr = 1.0f + ( (float) proc->waiting_time/proc->burst_time);

		if (rr > hrr){
			hrr = rr;
			hrr_proc_prev = prev;
		}
		else if (fabs(rr - hrr) < 1e-6){
			hrr_proc = hrr_proc_prev->next->object;
			if (hrr_proc->burst_time >= proc->burst_time){
				hrr_proc_prev = prev;
			}
		}
    }

	return dequeue_head(hrr_proc_prev);
}


static void enqueue_arrivals(process p[], int n, int time, queue_node *queue){
	for (int i = 0; i < n; i++){
		if (p[i].arrival_time == time){
			enqueue(&p[i], queue);
		}
	}
}

void hrrn(process p[], int n, int maxTime, char result[]){
	queue_node *queue = new_queue();
	if (!queue) return;

	process *running = NULL;

	int time = 0;
	
	while (time < maxTime){
		enqueue_arrivals(p, n, time, queue);

		if (running == NULL) running = dequeue_hrrn(time, queue);

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
