#include "stack.h"
#include "queue.h"
#include<stdlib.h>

//Implementation of stack related operations

// Initialization of the parking lot
CarStack* createStack(int capacity){
    CarStack* stack = (CarStack*) malloc(sizeof(CarStack));
    stack->cars = (Car*) malloc(sizeof(Car)*capacity);
    stack->capacity = capacity;
    stack->top = -1; // -1 indication the stack is empty
    return stack;
}

bool isStackFull(CarStack* stack){
    return stack->top == stack->capacity - 1;
}

bool isStackEmpty(CarStack* stack){
    return stack->top == -1;
}

// bool value indicates whether the push operation was executed successfully
bool push(CarStack* stack,Car car){
    // stack is full, unable to push
    if(isStackFull(stack)){
        return false;
    }
    stack->cars[++stack->top] = car;
    return true;
}

Car pop(CarStack* stack){
    if(isStackEmpty(stack)){
        Car emptyCar = {0,0};// wrong return
        return emptyCar;
    }
    return stack->cars[stack->top--];
}

Car peek(CarStack* stack){
    if(isStackEmpty(stack)){
        Car emptyCar = {0,0};// wrong return
        return emptyCar;
    }
    return stack->cars[stack->top];
}

// Initialization of the shortcut
CarQueue* createQueue(){
    CarQueue* queue = (CarQueue*)malloc(sizeof(CarQueue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// bool value indicates whether the enqueue operation was executed successfully
bool enqueue(CarQueue* queue,Car car){
    QueueNode *newNode = (QueueNode*) malloc(sizeof(CarQueue));
    if(newNode == NULL) return false;

    newNode->car = car;
    newNode->next = NULL;

    if(queue->rear == NULL){
        queue->front = queue->rear = newNode;
    }
    else{
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    return true;
}

Car deQueue(CarQueue* queue){
    if(queue->front == NULL){
        Car emptyCar = {0,0};
        return emptyCar;
    }

    QueueNode* temp = queue->front;
    queue->front = queue->front->next;

    // if there is only one car to deQueue, after deQueue, empty the queue
    if(queue->front == NULL){
        queue->rear = NULL;
    }

    Car car = temp->car;
    free(temp);
    return car;
}

bool isQueueEmpty(CarQueue* queue){
    return queue->front == NULL;
}