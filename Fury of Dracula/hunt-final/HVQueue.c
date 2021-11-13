#include <stdio.h> 
#include <stdlib.h> 

#include "HVQueue.h"
#include "Places.h"

////////////////////////////

struct Queue {
    int front;      //front of queue
    int rear;       //back of queue
    int size;      //the number of elements
    int capacity;   //maximum number of elements
    PlaceId *array; //pointer to array 
};
//make new queue
struct Queue* NewQueue(int capacity) {
    struct Queue* ToVisit = malloc(sizeof(struct Queue));
    ToVisit->capacity = capacity;
    ToVisit->front = ToVisit->size = 0;
    ToVisit->rear = 0;
    ToVisit->array = malloc(ToVisit->capacity * sizeof(PlaceId));
    return ToVisit; 
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
  
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, PlaceId p)
{
    if (isFull(queue))
        return;
    queue->array[queue->rear] = p;
    queue->rear = queue->rear + 1;
    queue->size = queue->size + 1;

}

// Function to remove an item from queue.
// It changes front and size
PlaceId dequeue(struct Queue* queue)
{
    PlaceId to_leave = queue->array[queue->front];
    queue->front = queue->front + 1;
    queue->size = queue->size - 1;
    return to_leave;
}
 
// Check if place is already in to-visit queue.
int isNotInQueue (struct Queue* queue, PlaceId p)
{
    int i = 0;
    while (i <= queue->size) {
        if (queue->array[i] == p) {
            return -1;
        }
    }
    return 1;
}
    

// drop the queue
void dropHunterQueue(struct Queue* queue) {
    free(queue->array);
    free(queue);
}




