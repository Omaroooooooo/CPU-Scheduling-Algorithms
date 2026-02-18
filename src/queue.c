#include "../header/queue.h"
#include <stdlib.h>

void enqueue(void *new_object, queue_node *head)
{
	queue_node *q = malloc(sizeof(queue_node));
	if (q == NULL) return;

	q->object = new_object;

    if (head->next == NULL) {
        q->next = NULL;
        head->next = q;
        return;
    }

    q->next = head->next;
    head->next = q;
}

void *dequeue(queue_node *head)
{
	if (head == NULL || head->next == NULL) return NULL;

	queue_node *curr = head;
	queue_node *prev = NULL;

	while (curr->next != NULL){
		prev = curr;
		curr = curr->next;
	}

	void *obj = curr->object;
	free(curr);
	prev->next = NULL;
	return obj;
}

void *dequeue_head(queue_node *head) 
{
	if (head == NULL || head->next == NULL) return NULL;

	queue_node *q = head->next;
	void *obj = q->object;
	head->next = q->next;
	free(q);
	return obj;
}

void *peek(queue_node *head)
{
    if (head == NULL || head->next == NULL) return NULL;

    queue_node *curr = head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    return curr->object;
}

queue_node *new_queue()
{
	queue_node *q = malloc(sizeof(queue_node));
	if (q == NULL) return NULL;
	q->next = NULL;
	q->object = NULL;
	return q;
}

void free_queue(queue_node *head)
{
	while (head != NULL){
		queue_node *next = head->next;
		free(head);
		head = next;
	}
}


