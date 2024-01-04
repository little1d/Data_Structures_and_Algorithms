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