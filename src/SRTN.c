#include "../header/SRTN.h"

static void enqueue_srtn(process *p, queue_node *queue){
    if (queue->next == NULL){
        enqueue(p, queue);
        return;
    } 

    process *proc;
    queue_node *prev = NULL;
    queue_node *curr = queue;

    while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
        proc = curr->object;
        if (p->time_left > proc->time_left ||
   		   (p->time_left == proc->time_left &&
    	   (p->arrival_time > proc->arrival_time ||
     	   (p->arrival_time == proc->arrival_time &&
      		p->id > proc->id))))
		{
    		enqueue(p, prev);
    		return;
		}
    }

    enqueue(p, curr);
}

static void enqueue_arrivals(process p[], int n, int time, queue_node *queue){
	for (int j = 0; j < n; j++){
		if (p[j].arrival_time == time){
			enqueue_srtn(&p[j], queue);
		}
	}
}

void srtn(process p[], int n, int maxTime, char result[]){
	queue_node *queue = new_queue();
	if (!queue) return;

	process *running = NULL;

	int time = 0;

	while (time < maxTime){
		enqueue_arrivals(p, n, time, queue);

		if (running == NULL) running = dequeue(queue);

		if (running != NULL){
			process *proc = peek(queue);
			if (proc != NULL && running->time_left > proc->time_left){
				enqueue_srtn(running, queue);
				running = dequeue(queue);
			}

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
