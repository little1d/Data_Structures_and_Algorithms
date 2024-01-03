#include "user_table_generate.h"
#include "business_table.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int userID;
    int arrivalTime;
    int processTime;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int totalTime; // Total time for users in the queue
} Queue;

// Function prototypes
void enqueue(Queue* q, int userID, int arrivalTime, int processTime);
QueueNode* dequeue(Queue* q);
Queue* createQueue();
void processUserTable(const char* filename);

int main() {
    generateUserTable();
    processUserTable("user_table_1.txt");
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
void enqueue(Queue* q, int userID, int arrivalTime, int processTime) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->userID = userID;
    newNode->arrivalTime = arrivalTime;
    newNode->processTime = processTime;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->totalTime += processTime;
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
    // 继续 main.c
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    Queue* windows[3];
    for (int i = 0; i < 3; i++) {
        windows[i] = createQueue(); // Create queues for each window
    }

    // Read and process each user from the file
    int userID, arrivalTime, businessType;
    while (fscanf(file, "%d %d %d", &userID, &arrivalTime, &businessType) != EOF) {
        int processTime = businessTable[businessType].processTime;

        // Find the shortest queue
        int minTimeWindow = 0;
        for (int i = 1; i < 3; i++) {
            if (windows[i]->totalTime < windows[minTimeWindow]->totalTime) {
                minTimeWindow = i;
            }
        }

        // Enqueue the user to the shortest queue
        enqueue(windows[minTimeWindow], userID, arrivalTime, processTime);
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
            fprintf(outFile, "User %d arrives at %d, starts at %d, processes for %d minutes.\n",
                    user->userID, user->arrivalTime, windows[i]->totalTime, user->processTime);
            free(user);
        }
        free(windows[i]);
    }

    fclose(outFile);
}
