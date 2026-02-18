#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct _queue_node {
	void *object;
	struct _queue_node *next;
} queue_node;

// Adds a new item right behind the very first element in the queue after the head. 
// Head acts as a placeholder for other items in the queue
void enqueue(void *new_object, queue_node *head);


// Gets and deletes the last item from the queue.
void *dequeue(queue_node *head);


// Gets and deletes the first item (after the head) from the queue.
void *dequeue_head(queue_node *head);


// Gets the last item in the queue without deleting it.
void *peek(queue_node *head);


// Creates and returns a new queue, which consists of a single queue element, that is the head element.
queue_node *new_queue();


// Deletes and frees all queue items.
void free_queue(queue_node *head);

#endif				//QUEUE_H
