/*
 * This header file uses a stack to simulate a shortcut and throws out related operation functions
 * Author: Harrison
 * Date: January 3, 2024
 */

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_QUEUE_H
#define DATA_STRUCTURES_AND_ALGORITHMS_QUEUE_H

#include<stdbool.h>
#include "stack.h"

typedef struct QueueNode{
    Car car;
    struct QueueNode* next;
}QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
}CarQueue;

CarQueue* createQueue();
bool enqueue(CarQueue* queue,Car car);
Car dequeue(CarQueue* queue);
bool isQueueEmpty(CarQueue* queue);

#endif //DATA_STRUCTURES_AND_ALGORITHMS_QUEUE_H
