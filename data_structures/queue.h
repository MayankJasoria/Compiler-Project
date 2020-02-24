/*  GROUP 48:
    PUNEET ANAND    2016B4A70487P
    MAYANK JASORIA  2016B1A70703P
    SHUBHAM TIWARI  2016B4A70935P
    VIBHAV OSWAL    2016B4A70594P */
	
#include "linked_list.h"
#include "../utils/utils.h"

typedef List Queue;

/**
 * Creates and returns a new queue
 * @return a new queue
 */
Queue getQueue();

/**
 * Adds a new element to back of the queue
 * @param queue	The queue to which data should be added
 * @param data	The data to be added to the queue
 * 
 * @return Updated queue
 */
Queue enqueue(Queue queue, void* data);

/**
 * Removes an element from the front of the queue
 * @param queue	The queue from which data is to be removed
 * 
 * @return Updated queue
 */
Queue dequeue(Queue queue);

/**
 * Returns the element at the front of the queue
 * @param queue	The queue whose front element is required
 * 
 * @return The element at the front of the queue
 */
void* frontElement(Queue queue);

/**
 * Returns the element at the back of the queue
 * @param queue	The queue whose back element is required
 * 
 * @return The element at the back of the queue
 */
void* backElement(Queue queue);

/**
 * Informs whether a given queue is empty or not
 * @return True if queue is empty, false otherwise
 */
boolean isQueueEmpty(Queue queue);