/*
 This header file is used to generate a user table.
 The user table information includes the user's id, the time the user arrives and the business required.
 Author: Harrison
 Date: January 3, 2024
*/

#ifndef USER_TABLE_GENERATE_H
#define  USER_TABLE_GENERATE_H
#include "business_table.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// User structure
typedef struct {
    int userId;
    BusinessType businessTypes[2]; // Maximum of 2 business types
    int arrivalTime; //
}User;

// Function declaration to generate user list
void generateUsers(const char *filename);


#endif //USER_TABLE_GENERATE_H