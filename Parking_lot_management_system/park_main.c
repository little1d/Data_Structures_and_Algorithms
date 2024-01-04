/*
 * This c source file Execute main logic
 * Author:Harrison
 * DATE: January 4, 2024
 */
#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int feePerMinute = 1;  // Assuming the parking fee is 1 unit per minute

int main() {
    int capacity = 5; // Assuming the parking lot capacity is 5
    CarStack* parkingLot = createStack(capacity);
    CarQueue* waitingLine = createQueue();

    while (1) {
        char operation[10];
        int plateNumber, time;

        printf("Enter operation (arrive or leave), plate number, and time (e.g., arrive 1001 10): ");
        scanf("%s %d %d", operation, &plateNumber, &time);

        if (strcmp(operation, "arrive") == 0) {
            Car newCar = {plateNumber, time, 0, 0};
            if (!isStackFull(parkingLot)) {
                push(parkingLot, newCar);
                printf("Car %d parked in the parking lot at position %d.\n", plateNumber, parkingLot->top + 1);
            } else {
                enqueue(waitingLine, newCar);
                printf("Car %d waiting in the line.\n", plateNumber);
            }
        } else if (strcmp(operation, "leave") == 0) {
            Car tempCar;
            CarStack* tempStack = createStack(capacity); // Temporary stack to move cars
            int found = 0;

            while (!isStackEmpty(parkingLot)) {
                tempCar = pop(parkingLot);
                if (tempCar.plateNumber == plateNumber) {
                    tempCar.leaveTime = time;
                    tempCar.fees = (tempCar.leaveTime - tempCar.arrivalTime) * feePerMinute;
                    printf("Car %d leaves. Stay duration: %d minutes. Fees: %d.\n", tempCar.plateNumber, tempCar.leaveTime - tempCar.arrivalTime, tempCar.fees);
                    found = 1;
                    break;
                }
                push(tempStack, tempCar);
            }

            if (!found) {
                printf("Car %d not found in the parking lot.\n", plateNumber);
            }

            // Move other cars back to the parking lot
            while (!isStackEmpty(tempStack)) {
                push(parkingLot, pop(tempStack));
            }

            // Move cars from the line into the parking lot
            while (!isStackFull(parkingLot) && !isQueueEmpty(waitingLine)) {
                Car carFromQueue = dequeue(waitingLine);
                push(parkingLot, carFromQueue);
                printf("Car %d from the line parked in the parking lot at position %d.\n", carFromQueue.plateNumber, parkingLot->top + 1);
            }

            free(tempStack->cars);
            free(tempStack);
        } else {
            printf("Invalid operation. Please enter 'arrive' or 'leave'.\n");
        }

        // Ask user if they want to continue
        printf("Do you want to continue? (yes or no): ");
        scanf("%s", operation);
        if (strcmp(operation, "no") == 0) {
            break;
        }
    }

    // Clean up resources
    free(parkingLot->cars);
    free(parkingLot);
    // Note: The queue nodes should also be freed

    return 0;
}
