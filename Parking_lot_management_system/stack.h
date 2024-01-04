/*
 * This header file uses a stack to simulate a parking lot and throws out related operation functions
 * Author: Harrison
 * Date: January 4, 2024
 */
#ifndef DATA_STRUCTURES_AND_ALGORITHMS_STACK_H
#define DATA_STRUCTURES_AND_ALGORITHMS_STACK_H

#include<stdbool.h>

// Car structure declaration
typedef struct {
    int plateNumber;
    int arrivalTime;
    int fees;
    int leaveTime;
}Car;

// Parking lot declaration
typedef struct{
    Car* cars;
    int capacity;
    int top;
}CarStack;

CarStack* createStack(int capacity);
bool isStackFull(CarStack* stack);
bool isStackEmpty(CarStack* stack);
bool push(CarStack* stack,Car car);
Car pop(CarStack* stack);
Car peek(CarStack* stack);

#endif //DATA_STRUCTURES_AND_ALGORITHMS_STACK_H
