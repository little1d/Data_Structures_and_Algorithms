#include "user_table_generate.h"
#include "business_table.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int userID;
    int arrivalTime;
    int startTime; // The Time when the user starts being served
    int processTime;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int totalTime; // Total time for users in the queue
} Queue;

// Function prototypes
void enqueue(Queue* q, int userID, int arrivalTime, int processTime, int startTime);
QueueNode* dequeue(Queue* q);
Queue* createQueue();
void processUserTable(const char* filename);

int main() {
    generateUsers("users_table.txt");
    processUserTable("users_table.txt");
    return 0;
}

// Create a queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->totalTime = 0;
    return q;
}

// Enqueue operation for the queue
void enqueue(Queue* q, int userID, int arrivalTime, int processTime, int startTime) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    newNode->userID = userID;
    newNode->arrivalTime = arrivalTime;
    newNode->processTime = processTime;
    newNode->startTime = startTime; // Add the startTime to the node
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->totalTime = (q->totalTime > arrivalTime ? q->totalTime : arrivalTime) + processTime;
}


// Dequeue operation for the queue
QueueNode* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;

    QueueNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) q->rear = NULL;
    q->totalTime -= temp->processTime;
    return temp;
}

// Process the user table
void processUserTable(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    Queue* windows[3];
    for (int i = 0; i < 3; i++) {
        windows[i] = createQueue();
    }

    // Read and process each user from the file
    int userID, arrivalTime, businessType1,businessType2;
    char businessTypesStr[10];  // Buffer to store business types as string
    while (fscanf(file, "User %d, Business type:%[^\n] , Arrival Time: %d\n", &userID, businessTypesStr, &arrivalTime) != EOF) {
        int processTime = 0;
        int numScanned = sscanf(businessTypesStr, "%d %d", &businessType1, &businessType2);

        // Calculate total process time based on the number of business types
        processTime += businessTable[businessType1].processTime;
        if (numScanned == 2) {
            processTime += businessTable[businessType2].processTime;
        }

        // Find the shortest queue
        int minTimeWindow = 0;
        for (int i = 1; i < 3; i++) {
            if (windows[i]->totalTime < windows[minTimeWindow]->totalTime) {
                minTimeWindow = i;
            }
        }

        // Calculate start time for the user
        int startTime = (windows[minTimeWindow]->totalTime > arrivalTime) ?
                        windows[minTimeWindow]->totalTime : arrivalTime;
        enqueue(windows[minTimeWindow], userID, arrivalTime, processTime, startTime);
    }

    fclose(file);

    // Output the user strategy to a file
    FILE* outFile = fopen("user_strategy.txt", "w");
    if (outFile == NULL) {
        perror("Error opening output file");
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        fprintf(outFile, "Window %d:\n", i + 1);
        while (windows[i]->front != NULL) {
            QueueNode* user = dequeue(windows[i]);
            int endTime = user->startTime + user->processTime;
            fprintf(outFile, "User %d arrives at %d, starts at %d, ends at %d, processes for %d minutes.\n",
                    user->userID, user->arrivalTime, user->startTime, endTime, user->processTime);
            free(user);
        }
        free(windows[i]);
    }

    fclose(outFile);
}

