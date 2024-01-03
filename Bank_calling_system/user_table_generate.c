//
// Created by 24315 on 2024/1/2.
//

// 用户表生成程序：用于随机生成用户、用户到达银行的时间和所需办理的业务，结果文件输出到文本文件 `user_table_1.txt`

// user_table.c
#include "business_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int userID;
    int arrivalTime; // in minutes
    BusinessType businessType;
} User;

void generateUserTable() {
    FILE *file = fopen("user_table_1.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    srand(time(NULL)); // Seed for random number generation
    for (int i = 0; i < 10; i++) {
        User user;
        user.userID = i;
        user.arrivalTime = rand() % 60; // Random time within an hour
        user.businessType = rand() % 5; // Random business type
        fprintf(file, "%d %d %d\n", user.userID, user.arrivalTime, user.businessType);
    }

    fclose(file);
}

int main() {
    generateUserTable();
    return 0;
}
