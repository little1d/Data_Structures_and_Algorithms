/*
  This header file defines business types and business processing times
  Author: Harrison
  Date: January 2, 2024
*/

#ifndef BUSINESS_TABLE_H // Prevent duplicate inclusion of header files
#define BUSINESS_TABLE_H

// Use enumeration types to store businessType
typedef enum {
    BUSINESS_A,
    BUSINESS_B,
    BUSINESS_C,
    BUSINESS_D,
    BUSINESS_E
} BusinessType;

typedef struct {
    BusinessType type;
    int processTime; // in minutes
} Business;

// Define the business processing times
static Business businessTable[5] = {
        {BUSINESS_A, 5}, // Business A takes 5 minutes
        {BUSINESS_B, 10}, // Business B takes 10 minutes
        {BUSINESS_C, 15}, // Business C takes 15 minutes
        {BUSINESS_D, 20}, // Business D takes 20 minutes
        {BUSINESS_E, 25}  // Business E takes 25 minutes
};

#endif // BUSINESS_TABLE_H
