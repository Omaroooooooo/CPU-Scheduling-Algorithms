#include "../header/MLFQ.h" 

#define LEVELS 4


static process *dequeue_mlfq(queue_node *queues[], int *level){
	for (int i = 0; i < LEVELS; i++){
        if (peek(queues[i]) != NULL){
            *level = i;
            return dequeue(queues[i]);
        }
    }
    return NULL;
}

static void enqueue_arrivals(process p[], int n, int time, queue_node *queue){
	for (int i = 0; i < n; i++){
		if (p[i].arrival_time == time){
			enqueue(&p[i], queue);
		}
	}
}

void mlfq(process p[], int n, int maxTime, char result[]){
	queue_node *queues[LEVELS];
	for (int i = 0; i < LEVELS; i++){
		queues[i] = new_queue();
		if (!queues[i]) return;
	}
	

	process *running = NULL;
	int level = 0;
	int quantums[LEVELS] = {1,2,4,8};
	int quantum;

	int time = 0;
	
	while (time < maxTime){
		enqueue_arrivals(p, n, time, queues[0]);

		if (running == NULL){
			running = dequeue_mlfq(queues, &level); 
			quantum = quantums[level];
		}

		if (running != NULL){
			if (quantum == 0){
				level = (level < 3) ? (level + 1) : level;
				enqueue(running, queues[level]);
				running = dequeue_mlfq(queues, &level);
				quantum = quantums[level];
			}

			running->time_left--;
			quantum--;
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
	
	for (int i = 0; i < LEVELS; i++){
		free_queue(queues[i]);
	}
}
