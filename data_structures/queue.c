#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

Queue getQueue() {
	return getList();
}

Queue enqueue(Queue queue, void* data) {
	if(queue == NULL) {
		printf("The given queue is undefined. Created a new queue\n");
	}
	return insertToList(queue, data, BACK);
}

Queue dequeue(Queue queue) {
	if(queue == NULL || queue->head == NULL) {
		fprintf(stderr, "The given queue is empty\n");
		return queue;
	}
	return deleteByNode(queue, queue->head);
}

void* frontElement(Queue queue) {
	if(queue == NULL || queue->head == NULL) {
		fprintf(stderr, "The given queue is empty\n");
		return NULL;
	}
	return queue->head;
}

void* backElement(Queue queue) {
	if(queue == NULL || queue->end == NULL) {
		fprintf(stderr, "The given queue is empty\n");
	}
	return queue->end;
}

boolean isQueueEmpty(Queue queue) {
	if (queue == NULL || queue->head == NULL) {
		return True;
	}
	return False;
}

void printQueue(Queue q, void (*printElement)(void* data)) {
    if(q == NULL) {
        fprintf(stderr, "The given queue is empty\n");
        return;
    }
    printf("Front of queue -> ");
    printList(q, printElement);
}